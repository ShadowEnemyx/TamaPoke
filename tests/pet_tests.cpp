#include <cstdlib>
#include <iostream>
#include <string>

#include "pet.h"
#include "species_chirp.h"
#include "time_utils.h"
#include "dayphase.h"

uint32_t gMockMillis = 0;
SerialMock Serial;

static int failures = 0;

#define EXPECT_TRUE(expr) do { \
  if (!(expr)) { \
    std::cerr << "FEHLER: " << __FILE__ << ":" << __LINE__ << ": " << #expr << "\n"; \
    failures++; \
  } \
} while (0)

#define EXPECT_EQ(actual, expected) do { \
  auto a = (actual); \
  auto e = (expected); \
  if (!(a == e)) { \
    std::cerr << "FEHLER: " << __FILE__ << ":" << __LINE__ << ": " << #actual \
              << " war " << +a << ", erwartet " << +e << "\n"; \
    failures++; \
  } \
} while (0)

static Pet hatchedPet(int16_t dex) {
  Pet pet;
  pet.chooseStarter(dex);
  pet.eggTap();
  pet.eggTap();
  pet.eggTap();
  return pet;
}

static void testEggHatchesChosenStarter() {
  Pet pet = hatchedPet(4);

  EXPECT_TRUE(!pet.isEgg());
  EXPECT_EQ(pet.speciesId, 4);
  EXPECT_TRUE(pet.isRegistered(4));
  EXPECT_EQ(pet.registeredCount(), 1);
}

static void testBattleStatsUseBaseGenesLevelAndTraining() {
  Pet pet = hatchedPet(4);
  pet.ageMinutes = 15 * MINUTES_PER_LEVEL;
  pet.geneAtk = 110;
  pet.geneDef = 90;
  pet.geneSpe = 100;
  pet.trAtk = 7;
  pet.trDef = 3;
  pet.trSpe = 11;

  EXPECT_EQ(pet.level(), 16);
  EXPECT_EQ(pet.atkStat(), 52 * 110 / 100 + 16 + 7);
  EXPECT_EQ(pet.defStat(), 43 * 90 / 100 + 16 + 3);
  EXPECT_EQ(pet.speStat(), 65 + 16 + 11);
}

static void testEvolutionRequiresLevelAndHealthyStats() {
  Pet pet = hatchedPet(4);
  pet.ageMinutes = 15 * MINUTES_PER_LEVEL;
  pet.fullness = 39;

  EXPECT_TRUE(!pet.canEvolveNow());
  EXPECT_TRUE(pet.wantEvolveButton());

  pet.fullness = 40;
  EXPECT_TRUE(pet.canEvolveNow());
  EXPECT_TRUE(pet.wantEvolveButton());

  pet.evolve();
  EXPECT_EQ(pet.prevSpeciesId, 4);
  EXPECT_EQ(pet.speciesId, 5);
  EXPECT_TRUE(pet.isRegistered(5));
}

static void testEvolveOfferStaysWhenStatsDipAndReoffersAtCap() {
  Pet pet = hatchedPet(56);  // Menki
  pet.fullness = pet.joy = pet.energy = pet.hygiene = 80;
  pet.ageMinutes = 26 * MINUTES_PER_LEVEL;  // Lv.27
  EXPECT_TRUE(!pet.evolutionUnlocked());
  EXPECT_TRUE(!pet.wantEvolveButton());

  pet.ageMinutes = 27 * MINUTES_PER_LEVEL;  // Lv.28
  pet.joy = 10;
  EXPECT_TRUE(pet.evolutionUnlocked());
  EXPECT_TRUE(pet.wantEvolveButton());
  EXPECT_TRUE(!pet.canEvolveNow());

  pet.declineEvolve();
  EXPECT_TRUE(!pet.wantEvolveButton());
  pet.ageMinutes = 28 * MINUTES_PER_LEVEL;  // Lv.29
  pet.joy = 80;
  EXPECT_TRUE(pet.wantEvolveButton());
  EXPECT_TRUE(pet.canEvolveNow());

  pet.ageMinutes = 99UL * MINUTES_PER_LEVEL;  // Lv.100
  pet.declineEvolve();
  EXPECT_TRUE(!pet.wantEvolveButton());
  pet.ageMinutes += 1440;
  EXPECT_TRUE(pet.wantEvolveButton());
}

static void testCareMistakeDelaysEvolution() {
  Pet pet = hatchedPet(4);
  pet.ageMinutes = 15 * MINUTES_PER_LEVEL;
  pet.careMistakes = 1;

  EXPECT_TRUE(!pet.canEvolveNow());

  pet.ageMinutes = 16 * MINUTES_PER_LEVEL;
  EXPECT_TRUE(pet.canEvolveNow());
}

static void testTrainingRewardsClampAndAffectNeeds() {
  Pet pet = hatchedPet(7);
  pet.trAtk = 95;
  pet.energy = 50;
  pet.fullness = 50;
  pet.weight = 30;

  uint8_t gain = pet.trainStrength(100);

  EXPECT_EQ(gain, 18);
  EXPECT_EQ(pet.trAtk, 100);
  EXPECT_EQ(pet.energy, 38);
  EXPECT_EQ(pet.fullness, 45);
  EXPECT_EQ(pet.weight, 0);
}

static void testCatchRewardTrainsSpeedAndRecord() {
  Pet pet = hatchedPet(7);
  pet.trSpe = 98;
  pet.energy = 20;
  pet.fullness = 9;
  pet.catchHi = 12;

  uint8_t gain = pet.applyCatchResult(18);

  EXPECT_EQ(gain, 6);
  EXPECT_EQ(pet.trSpe, 100);
  EXPECT_EQ(pet.catchHi, 18);
  EXPECT_TRUE(pet.energy >= 5);
  EXPECT_TRUE(pet.fullness >= 5);

  pet.applyCatchResult(5);
  EXPECT_EQ(pet.catchHi, 18);
}

static void testMemoRewardTrainsDefenseAndRecord() {
  Pet pet = hatchedPet(1);
  pet.trDef = 99;
  pet.energy = 12;
  pet.fullness = 7;
  pet.memoHi = 4;
  pet.bond = 1;

  uint8_t gain = pet.applyMemoResult(9);

  EXPECT_EQ(gain, 4);
  EXPECT_EQ(pet.trDef, 100);
  EXPECT_EQ(pet.memoHi, 9);
  EXPECT_TRUE(pet.energy >= 5);
  EXPECT_TRUE(pet.fullness >= 5);
  EXPECT_TRUE(pet.bond >= 3);

  pet.applyMemoResult(3);
  EXPECT_EQ(pet.memoHi, 9);
}

static void testCleanRewardImprovesHygieneAndRecord() {
  Pet pet = hatchedPet(7);
  pet.hygiene = 40;
  pet.energy = 12;
  pet.poops = 2;
  pet.cleanHi = 5;

  uint8_t gain = pet.applyCleanResult(9);

  EXPECT_EQ(gain, 4);
  EXPECT_EQ(pet.hygiene, 87);
  EXPECT_EQ(pet.cleanHi, 9);
  EXPECT_EQ(pet.poops, 1);
  EXPECT_TRUE(pet.energy >= 8);
}

static void testTypeRewardTrainsAttackAndRecord() {
  Pet pet = hatchedPet(4);
  pet.trAtk = 99;
  pet.energy = 12;
  pet.fullness = 7;
  pet.typeHi = 3;

  uint8_t gain = pet.applyTypeResult(12);

  EXPECT_EQ(gain, 3);
  EXPECT_EQ(pet.trAtk, 100);
  EXPECT_EQ(pet.typeHi, 12);
  EXPECT_TRUE(pet.energy >= 8);
  EXPECT_TRUE(pet.fullness >= 5);
}

static void testPetEventsRewardAndClamp() {
  Pet pet = hatchedPet(4);
  pet.fullness = 95;
  pet.joy = 98;

  EXPECT_TRUE(pet.applyPetEvent(PET_EVENT_BERRY));
  EXPECT_EQ(pet.fullness, 100);
  EXPECT_EQ(pet.joy, 100);

  pet.bond = 99;
  pet.joy = 95;
  EXPECT_TRUE(pet.applyPetEvent(PET_EVENT_HEART));
  EXPECT_EQ(pet.bond, 100);
  EXPECT_EQ(pet.joy, 100);

  pet.energy = 98;
  pet.hygiene = 50;
  pet.joy = 97;
  EXPECT_TRUE(pet.applyPetEvent(PET_EVENT_SPARKLE));
  EXPECT_EQ(pet.joy, 100);
  EXPECT_EQ(pet.hygiene, 53);
}

static void testPetEventsBlockedForEggAndCeremony() {
  Pet egg;
  EXPECT_TRUE(!egg.applyPetEvent(PET_EVENT_BERRY));

  Pet pet = hatchedPet(7);
  pet.ceremony = CER_FAREWELL;
  EXPECT_TRUE(!pet.applyPetEvent(PET_EVENT_HEART));
}

static void testPersonalityIsDerivedWithoutMutating() {
  Pet pet = hatchedPet(4);
  uint8_t joy = pet.joy;
  uint8_t energy = pet.energy;
  uint8_t fullness = pet.fullness;
  uint16_t wins = pet.battleWins;

  EXPECT_EQ(pet.personality(), PERS_BALANCED);
  EXPECT_EQ(pet.joy, joy);
  EXPECT_EQ(pet.energy, energy);
  EXPECT_EQ(pet.fullness, fullness);
  EXPECT_EQ(pet.battleWins, wins);

  Pet playful = hatchedPet(7);
  playful.catchHi = 18;
  EXPECT_EQ(playful.personality(), PERS_PLAYFUL);

  Pet brave = hatchedPet(25);
  brave.battleWins = 8;
  EXPECT_EQ(brave.personality(), PERS_BRAVE);

  Pet calm = hatchedPet(1);
  calm.bond = 45;
  calm.careMistakes = 1;
  EXPECT_EQ(calm.personality(), PERS_CALM);

  Pet lazy = hatchedPet(6);
  lazy.weight = 72;
  lazy.battleWins = 20;
  EXPECT_EQ(lazy.personality(), PERS_LAZY);
}

static void testDailyGoalsProgressAndReset() {
  Pet pet = hatchedPet(4);
  pet.setClock(86400);
  pet.ensureDailyGoals();

  EXPECT_EQ(pet.dailyGoalType[0], DAILY_GOAL_CARE);
  EXPECT_EQ(pet.dailyGoalType[1], DAILY_GOAL_PLAY);
  EXPECT_EQ(pet.dailyGoalType[2], DAILY_GOAL_CATCH);
  EXPECT_TRUE(!pet.dailyGoalComplete(0));

  pet.feedCandy();
  EXPECT_EQ(pet.dailyGoalProgress[0], 1);
  EXPECT_TRUE(pet.dailyGoalComplete(0));

  pet.playResult(10);
  EXPECT_EQ(pet.dailyGoalProgress[1], 1);
  EXPECT_TRUE(pet.dailyGoalComplete(1));

  pet.applyCatchResult(3);
  EXPECT_EQ(pet.dailyGoalProgress[2], 3);
  EXPECT_TRUE(!pet.dailyGoalComplete(2));
  pet.applyCatchResult(3);
  EXPECT_EQ(pet.dailyGoalProgress[2], 5);
  EXPECT_TRUE(pet.dailyGoalComplete(2));

  pet.setClock(2 * 86400);
  pet.ensureDailyGoals();
  EXPECT_EQ(pet.dailyGoalDay, 2U);
  EXPECT_EQ(pet.dailyGoalDone, 0);
  EXPECT_EQ(pet.dailyGoalProgress[0], 0);
}

static void testDailyBattleGoalCompletesOnWinOnly() {
  Pet pet = hatchedPet(4);
  pet.setClock(3 * 86400);
  pet.ensureDailyGoals();

  EXPECT_EQ(pet.dailyGoalType[2], DAILY_GOAL_BATTLE);
  pet.applyBattleLoss();
  EXPECT_EQ(pet.dailyGoalProgress[2], 0);
  EXPECT_TRUE(!pet.dailyGoalComplete(2));

  pet.applyBattleWin(66, false);
  EXPECT_EQ(pet.dailyGoalProgress[2], 1);
  EXPECT_TRUE(pet.dailyGoalComplete(2));
}

static void testCaughtDexIsSeparateFromRaisedDex() {
  Pet pet = hatchedPet(4);

  EXPECT_EQ(pet.caughtCount(), 0);
  EXPECT_EQ(pet.knownDexCount(), 1);
  EXPECT_TRUE(!pet.isRegistered(66));

  pet.registerCaught(66);
  EXPECT_TRUE(pet.isCaught(66));
  EXPECT_TRUE(!pet.isRegistered(66));
  EXPECT_EQ(pet.caughtCount(), 1);
  EXPECT_EQ(pet.knownDexCount(), 2);

  pet.registerCaught(66);
  EXPECT_EQ(pet.caughtCount(), 1);
  EXPECT_EQ(pet.knownDexCount(), 2);
}

static void testCaughtPokemonAdvanceDailyCatchGoal() {
  Pet pet = hatchedPet(4);
  pet.setClock(86400);
  pet.ensureDailyGoals();

  EXPECT_EQ(pet.dailyGoalType[2], DAILY_GOAL_CATCH);
  EXPECT_EQ(pet.dailyGoalProgress[2], 0);

  pet.registerCaught(66);
  EXPECT_EQ(pet.dailyGoalProgress[2], 1);
  EXPECT_TRUE(!pet.dailyGoalComplete(2));

  pet.registerCaught(67);
  EXPECT_EQ(pet.dailyGoalProgress[2], 2);
  EXPECT_TRUE(!pet.dailyGoalComplete(2));
}

static void testDexRewardsApplyOnceAndCap() {
  Pet pet = hatchedPet(4);
  pet.joy = 98;

  for (int16_t dex = 10; dex <= 18; dex++) pet.registerCaught(dex);

  EXPECT_EQ(pet.knownDexCount(), 10);
  EXPECT_EQ(pet.dexRewardMask & 0x01, 0x01);
  EXPECT_EQ(pet.joy, 100);
  uint8_t mask = pet.dexRewardMask;
  uint8_t joy = pet.joy;

  EXPECT_EQ(pet.applyDexRewards(), 0);
  EXPECT_EQ(pet.dexRewardMask, mask);
  EXPECT_EQ(pet.joy, joy);

  for (int16_t dex = 19; dex <= 33; dex++) pet.registerCaught(dex);
  EXPECT_EQ(pet.knownDexCount(), 25);
  EXPECT_TRUE((pet.dexRewardMask & 0x02) != 0);
  EXPECT_TRUE(pet.bond > 0);
}

static void testCollectionRanksAndFrameSelection() {
  Pet pet = hatchedPet(4);
  EXPECT_EQ(pet.collectionRank(), 0);
  EXPECT_EQ(pet.unlockedCollectionFrameCount(), 1);
  EXPECT_TRUE(pet.setCollectionFrame(0));
  EXPECT_TRUE(!pet.setCollectionFrame(1));

  for (int16_t dex = 5; dex <= 13; dex++) pet.registerCaught(dex);
  EXPECT_EQ(pet.knownDexCount(), 10);
  EXPECT_EQ(pet.collectionRank(), 1);
  EXPECT_EQ(pet.unlockedCollectionFrameCount(), 2);
  EXPECT_TRUE(pet.setCollectionFrame(1));
  EXPECT_EQ(pet.collectionFrame, 1);
  EXPECT_TRUE(!pet.setCollectionFrame(2));

  for (int16_t dex = 14; dex <= 28; dex++) pet.registerCaught(dex);
  EXPECT_EQ(pet.knownDexCount(), 25);
  EXPECT_EQ(pet.collectionRank(), 2);
  EXPECT_TRUE(pet.setCollectionFrame(2));
  EXPECT_EQ(pet.collectionFrame, 2);

  pet.registerCaught(28);  // bereits bekannt: kein doppelter Fortschritt
  EXPECT_EQ(pet.knownDexCount(), 25);
}

static void testSpeciesChirpProfilesAreValidAndIndividual() {
  uint16_t previousSignature = 0;
  for (int16_t dex = 1; dex <= DEX_COUNT; dex++) {
    SpeciesChirpProfile profile{};
    EXPECT_TRUE(speciesChirpProfile(dex, &profile));
    EXPECT_EQ(profile.count, 4);
    for (uint8_t i = 0; i < profile.count; i++) {
      EXPECT_TRUE(profile.notes[i].frequency >= 140 && profile.notes[i].frequency <= 2600);
      EXPECT_TRUE(profile.notes[i].durationMs >= 50 && profile.notes[i].durationMs <= 110);
      EXPECT_TRUE(profile.notes[i].volume >= 70 && profile.notes[i].volume <= 100);
      EXPECT_TRUE(profile.notes[i].wave <= CHIRP_SOFT);
    }
    uint16_t signature = profile.notes[2].frequency;
    EXPECT_TRUE(dex == 1 || signature != previousSignature);
    previousSignature = signature;
  }
  SpeciesChirpProfile invalid{};
  EXPECT_TRUE(!speciesChirpProfile(0, &invalid));
  EXPECT_TRUE(!speciesChirpProfile(DEX_COUNT + 1, &invalid));
  EXPECT_TRUE(!speciesChirpProfile(25, nullptr));
}

static void testPetInteractionCooldownAndPersonalityBonus() {
  Pet pet = hatchedPet(1);
  pet.ageMinutes = 20;
  pet.joy = 50;
  pet.bond = 10;

  uint8_t first = pet.interactPet(true);
  EXPECT_TRUE((first & PET_INTERACT_JOY) != 0);
  EXPECT_TRUE((first & PET_INTERACT_BOND) != 0);
  EXPECT_EQ(pet.joy, 52);
  EXPECT_EQ(pet.bond, 11);

  uint8_t again = pet.interactPet(true);
  EXPECT_EQ(again, PET_INTERACT_NONE);
  EXPECT_EQ(pet.joy, 52);
  EXPECT_EQ(pet.bond, 11);

  pet.ageMinutes = 30;
  pet.catchHi = 18;  // playful: more joy
  uint8_t later = pet.interactPet(false);
  EXPECT_TRUE((later & PET_INTERACT_JOY) != 0);
  EXPECT_EQ(pet.joy, 56);
}

static void testNewPetResetsInteractionAndDecisionDeferrals() {
  Pet pet = hatchedPet(4);
  pet.ageMinutes = 500;
  EXPECT_TRUE(pet.interactPet(false) != PET_INTERACT_NONE);
  pet.ageMinutes = 15 * MINUTES_PER_LEVEL;
  pet.declineEvolve();

  pet.newEgg();
  pet.chooseStarter(4);
  pet.eggTap();
  pet.eggTap();
  pet.eggTap();
  pet.ageMinutes = 1;
  EXPECT_TRUE(pet.interactPet(false) != PET_INTERACT_NONE);
  pet.ageMinutes = 15 * MINUTES_PER_LEVEL;
  EXPECT_TRUE(pet.wantEvolveButton());

  pet.newEgg();
  pet.chooseStarter(6);
  pet.eggTap();
  pet.eggTap();
  pet.eggTap();
  pet.ageMinutes = FAREWELL_AGE_MIN;
  pet.declineFarewell();
  pet.newEgg();
  pet.chooseStarter(6);
  pet.eggTap();
  pet.eggTap();
  pet.eggTap();
  pet.ageMinutes = FAREWELL_AGE_MIN;
  EXPECT_TRUE(pet.wantFarewellButton());
}

static void testLevelCapsAtOneHundred() {
  Pet pet = hatchedPet(4);
  pet.ageMinutes = 99UL * MINUTES_PER_LEVEL;
  EXPECT_EQ(pet.level(), 100);
  pet.ageMinutes = 300UL * MINUTES_PER_LEVEL;
  EXPECT_EQ(pet.level(), 100);
}

static void testCeremonyCompletesToNewEgg() {
  Pet pet = hatchedPet(6);
  gMockMillis = 100;
  pet.startFarewell();
  EXPECT_EQ(pet.ceremony, CER_FAREWELL);
  gMockMillis += CEREMONY_MS + 1;
  EXPECT_TRUE(pet.update(gMockMillis));
  EXPECT_TRUE(pet.isEgg());
  EXPECT_EQ(pet.lastEnd, CER_FAREWELL);
  gMockMillis = 0;
}

static void testDeadlineHelpersHandleMillisRollover() {
  uint32_t beforeWrap = UINT32_MAX - 20U;
  uint32_t deadline = beforeWrap + 40U;
  EXPECT_TRUE(deadlineActive(beforeWrap, deadline));
  EXPECT_TRUE(!deadlineReached(beforeWrap, deadline));
  EXPECT_EQ(deadlineRemaining(beforeWrap, deadline), 40U);
  uint32_t afterWrap = 20U;
  EXPECT_TRUE(!deadlineActive(afterWrap, deadline));
  EXPECT_TRUE(deadlineReached(afterWrap, deadline));
  EXPECT_EQ(deadlineRemaining(afterWrap, deadline), 0U);
}

static void testCatchChanceAndRolls() {
  Pet pet = hatchedPet(4);
  pet.bond = 40;

  uint8_t common = pet.catchChanceForWild(66, 5, 5, false);
  uint8_t rare = pet.catchChanceForWild(95, 5, 5, false);
  uint8_t highLevel = pet.catchChanceForWild(66, 12, 5, false);
  uint8_t close = pet.catchChanceForWild(66, 5, 5, true);

  EXPECT_TRUE(common > rare);
  EXPECT_TRUE(highLevel < common);
  EXPECT_TRUE(close > common);
  EXPECT_EQ(pet.catchChanceForWild(144, 5, 5, true), 0);

  EXPECT_TRUE(pet.tryCatchWild(66, 5, 5, false, common - 1));
  EXPECT_TRUE(pet.isCaught(66));
  EXPECT_TRUE(!pet.tryCatchWild(95, 5, 5, false, 99));
  EXPECT_TRUE(!pet.isCaught(95));
  EXPECT_TRUE(!pet.tryCatchWild(144, 5, 5, true, 0));
  EXPECT_TRUE(!pet.isCaught(144));
}

static void testRespectCatchIsLimitedAndHasNoCareReward() {
  Pet pet = hatchedPet(4);
  pet.bond = 40;
  pet.joy = 50;

  uint8_t normal = pet.catchChanceForWild(66, 5, 5, true);
  uint8_t respect = pet.respectCatchChanceForWild(66, 5, 5);

  EXPECT_TRUE(respect < normal);
  EXPECT_TRUE(respect >= 5);
  EXPECT_TRUE(respect <= 25);
  EXPECT_EQ(pet.respectCatchChanceForWild(144, 5, 5), 0);

  EXPECT_TRUE(pet.tryRespectCatchWild(66, 5, 5, respect - 1));
  EXPECT_TRUE(pet.isCaught(66));
  EXPECT_EQ(pet.joy, 50);
  EXPECT_EQ(pet.bond, 40);
}

static void testCareBonusCapsStreakContribution() {
  Pet pet;
  pet.streak = 99;
  pet.bond = 100;

  EXPECT_EQ(pet.careBonus(), 14);
}

static void testFarewellAndRunawayReadiness() {
  Pet pet = hatchedPet(6);
  pet.ageMinutes = FAREWELL_AGE_MIN;

  EXPECT_TRUE(pet.canFarewellNow());

  pet.sleeping = true;
  EXPECT_TRUE(!pet.canFarewellNow());

  pet.sleeping = false;
  pet.dbgRunawayReady();
  EXPECT_TRUE(pet.canRunawayNow());
}

static void testBattleRewardsAndProgression() {
  Pet pet = hatchedPet(25);
  pet.trDef = 99;
  pet.joy = 50;
  pet.energy = 25;
  pet.fullness = 12;
  pet.bond = 4;

  BattleReward common = pet.applyBattleWin(66, false);  // MACHOP: high ATK -> trains DEF

  EXPECT_EQ(common.stat, BATTLE_REWARD_DEF);
  EXPECT_EQ(common.amount, 1);
  EXPECT_EQ(pet.trDef, 100);
  EXPECT_EQ(pet.joy, 58);
  EXPECT_EQ(pet.energy, 20);
  EXPECT_EQ(pet.fullness, 10);
  EXPECT_TRUE(pet.bond >= 6);
  EXPECT_EQ(pet.battleWins, 1);
  EXPECT_EQ(pet.battleStreak, 1);
  EXPECT_EQ(pet.bestBattleStreak, 1);

  pet.trAtk = 98;
  BattleReward rare = pet.applyBattleWin(95, false);  // ONIX: rare, high DEF -> trains ATK

  EXPECT_EQ(rare.stat, BATTLE_REWARD_ATK);
  EXPECT_EQ(rare.amount, 2);
  EXPECT_EQ(pet.trAtk, 100);
  EXPECT_EQ(pet.battleWins, 2);
  EXPECT_EQ(pet.battleStreak, 2);
  EXPECT_EQ(pet.bestBattleStreak, 2);

  BattleReward close = pet.applyBattleWin(100, true);  // VOLTORB: high SPE -> trains SPE
  EXPECT_EQ(close.stat, BATTLE_REWARD_SPE);
  EXPECT_EQ(close.amount, 2);
  EXPECT_EQ(pet.battleStreak, 3);
  EXPECT_EQ(pet.bestBattleStreak, 3);

  pet.joy = 21;
  pet.energy = 22;
  pet.fullness = 11;
  pet.applyBattleLoss();

  EXPECT_EQ(pet.battleLosses, 1);
  EXPECT_EQ(pet.battleStreak, 0);
  EXPECT_EQ(pet.bestBattleStreak, 3);
  EXPECT_EQ(pet.joy, 20);
  EXPECT_EQ(pet.energy, 20);
  EXPECT_EQ(pet.fullness, 10);
}

static void testExpeditionStartAndClaim() {
  Pet pet = hatchedPet(4);
  pet.energy = 100;

  EXPECT_TRUE(pet.canStartExpedition(15, 1000));
  EXPECT_TRUE(pet.startExpedition(15, 1000, 99, 2));
  EXPECT_EQ(pet.energy, 88);
  EXPECT_EQ(pet.expeditionEndEpoch, 1900u);
  EXPECT_EQ(pet.expeditionRewardItem, EXP_ITEM_CARE);
  EXPECT_TRUE(pet.expeditionActive(1899));
  EXPECT_TRUE(!pet.expeditionReady(1899));
  EXPECT_TRUE(!pet.startExpedition(30, 1100, 0));
  EXPECT_EQ(pet.claimExpedition(1899), EXP_ITEM_NONE);

  EXPECT_EQ(pet.claimExpedition(1900), EXP_ITEM_CARE);
  EXPECT_EQ(pet.itemCounts[EXP_ITEM_CARE], 1);
  EXPECT_EQ(pet.expeditionEndEpoch, 0u);
  EXPECT_EQ(pet.expeditionRewardItem, EXP_ITEM_NONE);
}

static void testExpeditionRequirementsAndTrainingChances() {
  Pet egg;
  EXPECT_TRUE(!egg.canStartExpedition(15, 1000));
  EXPECT_EQ(egg.itemCounts[0], 0);

  Pet pet = hatchedPet(1);
  pet.energy = 100;
  EXPECT_EQ(Pet::expeditionEnergyCost(15), 12);
  EXPECT_EQ(Pet::expeditionEnergyCost(30), 20);
  EXPECT_EQ(Pet::expeditionEnergyCost(60), 32);
  EXPECT_EQ(Pet::expeditionEnergyCost(20), 255);
  EXPECT_EQ(pet.expeditionTrainingChance(15), 8);
  EXPECT_EQ(pet.expeditionTrainingChance(30), 15);
  EXPECT_EQ(pet.expeditionTrainingChance(60), 25);

  pet.fullness = pet.joy = pet.energy = pet.hygiene = 60;
  pet.bond = 20;
  EXPECT_EQ(pet.expeditionTrainingChance(15), 13);
  EXPECT_EQ(pet.expeditionTrainingChance(30), 22);
  EXPECT_EQ(pet.expeditionTrainingChance(60), 35);

  pet.fullness = pet.joy = pet.energy = pet.hygiene = 80;
  pet.bond = 50;
  EXPECT_EQ(pet.expeditionTrainingChance(15), 18);
  EXPECT_EQ(pet.expeditionTrainingChance(30), 30);
  EXPECT_EQ(pet.expeditionTrainingChance(60), 45);

  pet.sleeping = true;
  EXPECT_TRUE(!pet.canStartExpedition(15, 1000));
  pet.sleeping = false;
  pet.energy = 11;
  EXPECT_TRUE(!pet.canStartExpedition(15, 1000));
  pet.energy = 100;
  pet.ceremony = CER_FAREWELL;
  EXPECT_TRUE(!pet.canStartExpedition(15, 1000));
  pet.ceremony = CER_NONE;
  for (uint8_t i = 0; i < EXP_ITEM_COUNT; i++) pet.itemCounts[i] = EXP_ITEM_MAX;
  EXPECT_TRUE(pet.expeditionInventoryFull());
  EXPECT_TRUE(!pet.canStartExpedition(15, 1000));
}

static void testExpeditionItemsCapAndConsumeSafely() {
  Pet pet = hatchedPet(7);
  pet.itemCounts[EXP_ITEM_SNACK] = 1;
  pet.fullness = 90;
  pet.joy = 98;
  EXPECT_TRUE(pet.useExpeditionItem(EXP_ITEM_SNACK));
  EXPECT_EQ(pet.fullness, 100);
  EXPECT_EQ(pet.joy, 100);
  EXPECT_EQ(pet.itemCounts[EXP_ITEM_SNACK], 0);

  pet.itemCounts[EXP_ITEM_ENERGY] = 1;
  pet.energy = 80;
  EXPECT_TRUE(pet.useExpeditionItem(EXP_ITEM_ENERGY));
  EXPECT_EQ(pet.energy, 100);

  pet.itemCounts[EXP_ITEM_CARE] = 1;
  pet.hygiene = 80;
  pet.poops = 1;
  EXPECT_TRUE(pet.useExpeditionItem(EXP_ITEM_CARE));
  EXPECT_EQ(pet.hygiene, 100);
  EXPECT_EQ(pet.poops, 0);

  pet.itemCounts[EXP_ITEM_TRAIN] = 1;
  pet.trAtk = 99;
  EXPECT_TRUE(!pet.useExpeditionItem(EXP_ITEM_TRAIN));
  EXPECT_EQ(pet.itemCounts[EXP_ITEM_TRAIN], 1);
  EXPECT_TRUE(pet.useExpeditionItem(EXP_ITEM_TRAIN, TRAIN_STAT_ATK));
  EXPECT_EQ(pet.trAtk, 100);
  EXPECT_EQ(pet.itemCounts[EXP_ITEM_TRAIN], 0);

  pet.itemCounts[EXP_ITEM_TRAIN] = 1;
  pet.trAtk = pet.trDef = pet.trSpe = 100;
  EXPECT_TRUE(!pet.useExpeditionItem(EXP_ITEM_TRAIN, TRAIN_STAT_DEF));
  EXPECT_EQ(pet.itemCounts[EXP_ITEM_TRAIN], 1);
}

static void testExpeditionHudStates() {
  Pet egg;
  EXPECT_EQ(egg.expeditionHudState(1000), EXP_HUD_HIDDEN);

  Pet pet = hatchedPet(4);
  EXPECT_EQ(pet.expeditionHudState(1000), EXP_HUD_HIDDEN);

  pet.itemCounts[EXP_ITEM_SNACK] = 2;
  pet.itemCounts[EXP_ITEM_TRAIN] = 1;
  EXPECT_EQ(pet.expeditionItemCount(), 3);
  EXPECT_EQ(pet.expeditionHudState(1000), EXP_HUD_BAG);

  pet.expeditionEndEpoch = 1100;
  pet.expeditionRewardItem = EXP_ITEM_CARE;
  EXPECT_EQ(pet.expeditionHudState(1099), EXP_HUD_ACTIVE);
  EXPECT_EQ(pet.expeditionHudState(1100), EXP_HUD_READY);

  pet.ceremony = CER_FAREWELL;
  EXPECT_EQ(pet.expeditionHudState(1100), EXP_HUD_HIDDEN);
}

static const uint32_t kNoonEpoch = 1767276000UL;   // 2026-01-01 14:00 UTC
static const uint32_t kNightEpoch = 1767225600UL;  // 2026-01-01 00:00 UTC
static const uint32_t kMorningEpoch = 1767254400UL; // 2026-01-01 08:00 UTC

static void testDayphaseHelpers() {
  EXPECT_EQ(sceneHourFromEpoch(0), 13);
  EXPECT_EQ(sceneHourFromEpoch(kNoonEpoch), 14);
  EXPECT_EQ(sceneHourFromEpoch(kNightEpoch), 0);
  EXPECT_EQ(sceneHourFromEpoch(kMorningEpoch), 8);
  EXPECT_EQ(dayPhaseFromEpoch(kMorningEpoch), 0);
  EXPECT_EQ(dayPhaseFromEpoch(kNoonEpoch), 1);
  EXPECT_EQ(dayPhaseFromEpoch(kNightEpoch), 3);
  EXPECT_EQ(nightFoodDrop(kNoonEpoch), 2);
  EXPECT_EQ(nightFoodDrop(kNightEpoch), 1);
  EXPECT_TRUE(isVisualNight(20, false));
  EXPECT_TRUE(!isVisualNight(14, false));
  EXPECT_TRUE(isVisualNight(14, true));
}

static void testNightHungerDropsSlowerWhenAwake() {
  Pet dayPet = hatchedPet(4);
  dayPet.fullness = 80;
  dayPet.sleeping = false;
  dayPet.lastSeenEpoch = kNoonEpoch;
  gMockMillis = 0;
  EXPECT_TRUE(dayPet.update(PET_TICK_MS));
  EXPECT_EQ(dayPet.fullness, 78);

  Pet nightPet = hatchedPet(4);
  nightPet.fullness = 80;
  nightPet.sleeping = false;
  nightPet.lastSeenEpoch = kNightEpoch;
  gMockMillis = 0;
  EXPECT_TRUE(nightPet.update(PET_TICK_MS));
  EXPECT_EQ(nightPet.fullness, 79);
  gMockMillis = 0;
}

static void testOfflineNightHungerUsesHourOfEachMinute() {
  Pet pet = hatchedPet(4);
  pet.setClock(kNightEpoch);
  pet.fullness = 80;
  pet.sleeping = false;
  pet.syncClock(kNightEpoch + 5UL * 60UL);
  EXPECT_EQ(pet.fullness, 75);

  Pet dayPet = hatchedPet(4);
  dayPet.setClock(kNoonEpoch);
  dayPet.fullness = 80;
  dayPet.sleeping = false;
  dayPet.syncClock(kNoonEpoch + 5UL * 60UL);
  EXPECT_EQ(dayPet.fullness, 70);
}

static void testShakePlayHasCooldownAndDailyCap() {
  Pet pet = hatchedPet(4);
  pet.joy = 50;
  pet.lastSeenEpoch = kNoonEpoch;
  gMockMillis = 1000;
  EXPECT_TRUE(pet.applyShake());
  EXPECT_EQ(pet.joy, 53);
  EXPECT_TRUE(!pet.applyShake());
  gMockMillis += 25000;
  EXPECT_TRUE(pet.applyShake());
  EXPECT_EQ(pet.joy, 56);

  pet.sleeping = true;
  gMockMillis += 25000;
  EXPECT_TRUE(!pet.applyShake());
  pet.sleeping = false;

  for (int i = 0; i < 6; i++) {
    gMockMillis += 25000;
    EXPECT_TRUE(pet.applyShake());
  }
  gMockMillis += 25000;
  EXPECT_TRUE(!pet.applyShake());
  gMockMillis = 0;
}

static void testWalkGivesCappedJoyAndBond() {
  Pet pet = hatchedPet(4);
  pet.joy = 40;
  pet.bond = 10;
  pet.lastSeenEpoch = kNoonEpoch;
  EXPECT_EQ(pet.applyWalk(40), 1);
  EXPECT_EQ(pet.joy, 41);
  EXPECT_EQ(pet.applyWalk(40 * 10), 5);
  EXPECT_EQ(pet.joy, 46);

  Pet bonded = hatchedPet(4);
  bonded.bond = 10;
  bonded.lastSeenEpoch = kNoonEpoch;
  bonded.applyWalk(150);
  EXPECT_EQ(bonded.bond, 11);
  bonded.applyWalk(150);
  EXPECT_EQ(bonded.bond, 12);
  bonded.applyWalk(150);
  EXPECT_EQ(bonded.bond, 12);

  Pet egg;
  egg.speciesId = -1;
  EXPECT_EQ(egg.applyWalk(80), 0);
}

static void testMorningGreetingOncePerDay() {
  Pet pet = hatchedPet(4);
  pet.joy = 40;
  pet.lastSeenEpoch = kMorningEpoch;
  EXPECT_TRUE(pet.takeMorningGreeting());
  EXPECT_EQ(pet.joy, 42);
  EXPECT_TRUE(!pet.takeMorningGreeting());

  pet.lastSeenEpoch = kNoonEpoch;
  EXPECT_TRUE(!pet.takeMorningGreeting());
}

static void testGen2StarterFamiliesAndDexCompletion() {
  EXPECT_EQ(DEX_TBL[152].evolvesTo, 153);
  EXPECT_EQ(DEX_TBL[153].evolvesTo, 154);
  EXPECT_EQ(DEX_TBL[155].evolvesTo, 156);
  EXPECT_EQ(DEX_TBL[156].evolvesTo, 157);
  EXPECT_EQ(DEX_TBL[158].evolvesTo, 159);
  EXPECT_EQ(DEX_TBL[159].evolvesTo, 160);
  EXPECT_EQ(DEX_TBL[152].bHp, 45);
  EXPECT_EQ(DEX_TBL[157].bSpe, 100);
  EXPECT_EQ(DEX_TBL[160].bAtk, 105);

  Pet pet = hatchedPet(152);
  EXPECT_EQ(pet.speciesId, 152);
  EXPECT_TRUE(pet.isRegistered(152));
  EXPECT_TRUE(!pet.isRegistered(160));

  for (int16_t dex = 1; dex <= DEX_COUNT; dex++) pet.registerCaught(dex);
  EXPECT_EQ(pet.knownDexCount(), DEX_COUNT);
  EXPECT_EQ(pet.collectionRank(), 6);
  EXPECT_EQ(pet.nextDexGoal(), DEX_COUNT);
  EXPECT_EQ(pet.unlockedCollectionFrameCount(), 7);
  EXPECT_TRUE(pet.setCollectionFrame(6));
}

int main() {
  testEggHatchesChosenStarter();
  testBattleStatsUseBaseGenesLevelAndTraining();
  testEvolutionRequiresLevelAndHealthyStats();
  testEvolveOfferStaysWhenStatsDipAndReoffersAtCap();
  testCareMistakeDelaysEvolution();
  testTrainingRewardsClampAndAffectNeeds();
  testCatchRewardTrainsSpeedAndRecord();
  testMemoRewardTrainsDefenseAndRecord();
  testCleanRewardImprovesHygieneAndRecord();
  testTypeRewardTrainsAttackAndRecord();
  testPetEventsRewardAndClamp();
  testPetEventsBlockedForEggAndCeremony();
  testPersonalityIsDerivedWithoutMutating();
  testDailyGoalsProgressAndReset();
  testDailyBattleGoalCompletesOnWinOnly();
  testCaughtDexIsSeparateFromRaisedDex();
  testCaughtPokemonAdvanceDailyCatchGoal();
  testDexRewardsApplyOnceAndCap();
  testCollectionRanksAndFrameSelection();
  testSpeciesChirpProfilesAreValidAndIndividual();
  testPetInteractionCooldownAndPersonalityBonus();
  testNewPetResetsInteractionAndDecisionDeferrals();
  testLevelCapsAtOneHundred();
  testCeremonyCompletesToNewEgg();
  testDeadlineHelpersHandleMillisRollover();
  testCatchChanceAndRolls();
  testRespectCatchIsLimitedAndHasNoCareReward();
  testCareBonusCapsStreakContribution();
  testFarewellAndRunawayReadiness();
  testBattleRewardsAndProgression();
  testExpeditionStartAndClaim();
  testExpeditionRequirementsAndTrainingChances();
  testExpeditionItemsCapAndConsumeSafely();
  testExpeditionHudStates();
  testDayphaseHelpers();
  testNightHungerDropsSlowerWhenAwake();
  testOfflineNightHungerUsesHourOfEachMinute();
  testShakePlayHasCooldownAndDailyCap();
  testWalkGivesCappedJoyAndBond();
  testMorningGreetingOncePerDay();
  testGen2StarterFamiliesAndDexCompletion();

  if (failures) {
    std::cerr << failures << " Testfehler\n";
    return EXIT_FAILURE;
  }

  std::cout << "Alle pet.cpp-Tests bestanden\n";
  return EXIT_SUCCESS;
}
