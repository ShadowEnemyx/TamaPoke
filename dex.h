#pragma once
#include <stdint.h>

// GENERADO por tools/gen_dex.py desde tools/dex_data.py - no editar

#define DEX_COUNT 386
#define DEX_BITMAP_BYTES ((DEX_COUNT + 7) / 8)
#define DEX_EEVEE 133  // rama: 134/135/136/196/197

#define DEX_LANG_COUNT 6

// rareza: 0 = solo por evolucion, 1 = comun, 2 = raro, 3 = legendario
enum : uint8_t { R_EVO = 0, R_COMUN, R_RARO, R_LEGENDARIO };

// tipos de combate: datos actuales de las especies incluidas
enum : uint8_t {
  TYPE_NONE = 0, TYPE_NORMAL, TYPE_FIRE, TYPE_WATER, TYPE_ELECTRIC, TYPE_GRASS,
  TYPE_ICE, TYPE_FIGHTING, TYPE_POISON, TYPE_GROUND, TYPE_FLYING, TYPE_PSYCHIC,
  TYPE_BUG, TYPE_ROCK, TYPE_GHOST, TYPE_DRAGON, TYPE_DARK, TYPE_STEEL, TYPE_FAIRY
};

enum EvolutionCondition : uint8_t {
  EVO_LEVEL = 0, EVO_BOND, EVO_DAY_BOND, EVO_NIGHT_BOND,
  EVO_ATK_GT_DEF, EVO_DEF_GT_ATK, EVO_ATK_EQ_DEF
};
struct EvolutionRule {
  uint16_t from;
  uint16_t to;
  uint8_t minLevel;
  uint8_t condition;
};

struct DexEntry {
  const char *name;
  uint16_t evolvesTo;   // numero de dex, 0 = forma final
  uint8_t evolveLevel;
  uint8_t rarity;       // sale de huevo si > 0
  uint16_t accent;      // color RGB565 del tipo para la UI
  uint8_t bHp, bAtk, bDef, bSpe;  // base stats reales de gen 1
  uint8_t type1, type2; // tipos de combate, TYPE_NONE si no hay secundario
  uint8_t biome;        // 0 pradera 1 playa 2 bosque 3 volcan 4 montana 5 nieve
};

static const DexEntry DEX_TBL[DEX_COUNT + 1] = {
  { "?", 0, 0, 0, 0x2946, 50, 50, 50, 50, TYPE_NONE, TYPE_NONE, 0 },  // 0: sin usar
  { "BULBASAUR", 2, 16, R_COMUN, 0x3C49, 45, 49, 49, 45, TYPE_GRASS, TYPE_POISON, 2 },  // 1 grass/poison
  { "IVYSAUR", 3, 32, R_EVO, 0x3C49, 60, 62, 63, 60, TYPE_GRASS, TYPE_POISON, 2 },  // 2 grass/poison
  { "VENUSAUR", 0, 0, R_EVO, 0x3C49, 80, 82, 83, 80, TYPE_GRASS, TYPE_POISON, 2 },  // 3 grass/poison
  { "CHARMANDER", 5, 16, R_COMUN, 0xEA87, 39, 52, 43, 65, TYPE_FIRE, TYPE_NONE, 3 },  // 4 fire
  { "CHARMELEON", 6, 36, R_EVO, 0xEA87, 58, 64, 58, 80, TYPE_FIRE, TYPE_NONE, 3 },  // 5 fire
  { "CHARIZARD", 0, 0, R_EVO, 0xEA87, 78, 84, 78, 100, TYPE_FIRE, TYPE_FLYING, 3 },  // 6 fire/flying
  { "SQUIRTLE", 8, 16, R_COMUN, 0x4C98, 44, 48, 65, 43, TYPE_WATER, TYPE_NONE, 1 },  // 7 water
  { "WARTORTLE", 9, 36, R_EVO, 0x4C98, 59, 63, 80, 58, TYPE_WATER, TYPE_NONE, 1 },  // 8 water
  { "BLASTOISE", 0, 0, R_EVO, 0x4C98, 79, 83, 100, 78, TYPE_WATER, TYPE_NONE, 1 },  // 9 water
  { "CATERPIE", 11, 7, R_COMUN, 0x7CC4, 45, 30, 35, 45, TYPE_BUG, TYPE_NONE, 2 },  // 10 bug
  { "METAPOD", 12, 10, R_EVO, 0x7CC4, 50, 20, 55, 30, TYPE_BUG, TYPE_NONE, 2 },  // 11 bug
  { "BUTTERFREE", 0, 0, R_EVO, 0x7CC4, 60, 45, 50, 70, TYPE_BUG, TYPE_FLYING, 2 },  // 12 bug/flying
  { "WEEDLE", 14, 7, R_COMUN, 0x7CC4, 40, 35, 30, 50, TYPE_BUG, TYPE_POISON, 2 },  // 13 bug/poison
  { "KAKUNA", 15, 10, R_EVO, 0x7CC4, 45, 25, 50, 35, TYPE_BUG, TYPE_POISON, 2 },  // 14 bug/poison
  { "BEEDRILL", 0, 0, R_EVO, 0x7CC4, 65, 90, 40, 75, TYPE_BUG, TYPE_POISON, 2 },  // 15 bug/poison
  { "PIDGEY", 17, 18, R_COMUN, 0x8C4D, 40, 45, 40, 56, TYPE_NORMAL, TYPE_FLYING, 0 },  // 16 normal/flying
  { "PIDGEOTTO", 18, 36, R_EVO, 0x8C4D, 63, 60, 55, 71, TYPE_NORMAL, TYPE_FLYING, 0 },  // 17 normal/flying
  { "PIDGEOT", 0, 0, R_EVO, 0x8C4D, 83, 80, 75, 101, TYPE_NORMAL, TYPE_FLYING, 0 },  // 18 normal/flying
  { "RATTATA", 20, 20, R_COMUN, 0x8C4D, 30, 56, 35, 72, TYPE_NORMAL, TYPE_NONE, 0 },  // 19 normal
  { "RATICATE", 0, 0, R_EVO, 0x8C4D, 55, 81, 60, 97, TYPE_NORMAL, TYPE_NONE, 0 },  // 20 normal
  { "SPEAROW", 22, 20, R_COMUN, 0x8C4D, 40, 60, 30, 70, TYPE_NORMAL, TYPE_FLYING, 0 },  // 21 normal/flying
  { "FEAROW", 0, 0, R_EVO, 0x8C4D, 65, 90, 65, 100, TYPE_NORMAL, TYPE_FLYING, 0 },  // 22 normal/flying
  { "EKANS", 24, 22, R_COMUN, 0x8A73, 35, 60, 44, 55, TYPE_POISON, TYPE_NONE, 0 },  // 23 poison
  { "ARBOK", 0, 0, R_EVO, 0x8A73, 60, 95, 69, 80, TYPE_POISON, TYPE_NONE, 0 },  // 24 poison
  { "PIKACHU", 26, 30, R_EVO, 0xBCA1, 35, 55, 40, 90, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 25 electric
  { "RAICHU", 0, 0, R_EVO, 0xBCA1, 60, 90, 55, 110, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 26 electric
  { "SANDSHREW", 28, 22, R_COMUN, 0xB447, 50, 75, 85, 40, TYPE_GROUND, TYPE_NONE, 4 },  // 27 ground
  { "SANDSLASH", 0, 0, R_EVO, 0xB447, 75, 100, 110, 65, TYPE_GROUND, TYPE_NONE, 4 },  // 28 ground
  { "NIDORAN H", 30, 16, R_COMUN, 0x8A73, 55, 47, 52, 41, TYPE_POISON, TYPE_NONE, 0 },  // 29 poison
  { "NIDORINA", 31, 30, R_EVO, 0x8A73, 70, 62, 67, 56, TYPE_POISON, TYPE_NONE, 0 },  // 30 poison
  { "NIDOQUEEN", 0, 0, R_EVO, 0x8A73, 90, 92, 87, 76, TYPE_POISON, TYPE_GROUND, 0 },  // 31 poison/ground
  { "NIDORAN M", 33, 16, R_COMUN, 0x8A73, 46, 57, 40, 50, TYPE_POISON, TYPE_NONE, 0 },  // 32 poison
  { "NIDORINO", 34, 30, R_EVO, 0x8A73, 61, 72, 57, 65, TYPE_POISON, TYPE_NONE, 0 },  // 33 poison
  { "NIDOKING", 0, 0, R_EVO, 0x8A73, 81, 102, 77, 85, TYPE_POISON, TYPE_GROUND, 0 },  // 34 poison/ground
  { "CLEFAIRY", 36, 30, R_EVO, 0x8C4D, 70, 45, 48, 35, TYPE_FAIRY, TYPE_NONE, 0 },  // 35 fairy
  { "CLEFABLE", 0, 0, R_EVO, 0x8C4D, 95, 70, 73, 60, TYPE_FAIRY, TYPE_NONE, 0 },  // 36 fairy
  { "VULPIX", 38, 30, R_COMUN, 0xEA87, 38, 41, 40, 65, TYPE_FIRE, TYPE_NONE, 3 },  // 37 fire
  { "NINETALES", 0, 0, R_EVO, 0xEA87, 73, 76, 75, 100, TYPE_FIRE, TYPE_NONE, 3 },  // 38 fire
  { "JIGGLYPUFF", 40, 30, R_EVO, 0x8C4D, 115, 45, 20, 20, TYPE_NORMAL, TYPE_FAIRY, 0 },  // 39 normal/fairy
  { "WIGGLYTUFF", 0, 0, R_EVO, 0x8C4D, 140, 70, 45, 45, TYPE_NORMAL, TYPE_FAIRY, 0 },  // 40 normal/fairy
  { "ZUBAT", 42, 22, R_COMUN, 0x8A73, 40, 45, 35, 55, TYPE_POISON, TYPE_FLYING, 0 },  // 41 poison/flying
  { "GOLBAT", 0, 0, R_EVO, 0x8A73, 75, 80, 70, 90, TYPE_POISON, TYPE_FLYING, 0 },  // 42 poison/flying
  { "ODDISH", 44, 21, R_COMUN, 0x3C49, 45, 50, 55, 30, TYPE_GRASS, TYPE_POISON, 2 },  // 43 grass/poison
  { "GLOOM", 45, 36, R_EVO, 0x3C49, 60, 65, 70, 40, TYPE_GRASS, TYPE_POISON, 2 },  // 44 grass/poison
  { "VILEPLUME", 0, 0, R_EVO, 0x3C49, 75, 80, 85, 50, TYPE_GRASS, TYPE_POISON, 2 },  // 45 grass/poison
  { "PARAS", 47, 24, R_COMUN, 0x7CC4, 35, 70, 55, 25, TYPE_BUG, TYPE_GRASS, 2 },  // 46 bug/grass
  { "PARASECT", 0, 0, R_EVO, 0x7CC4, 60, 95, 80, 30, TYPE_BUG, TYPE_GRASS, 2 },  // 47 bug/grass
  { "VENONAT", 49, 31, R_COMUN, 0x7CC4, 60, 55, 50, 45, TYPE_BUG, TYPE_POISON, 2 },  // 48 bug/poison
  { "VENOMOTH", 0, 0, R_EVO, 0x7CC4, 70, 65, 60, 90, TYPE_BUG, TYPE_POISON, 2 },  // 49 bug/poison
  { "DIGLETT", 51, 26, R_COMUN, 0xB447, 10, 55, 25, 95, TYPE_GROUND, TYPE_NONE, 4 },  // 50 ground
  { "DUGTRIO", 0, 0, R_EVO, 0xB447, 35, 100, 50, 120, TYPE_GROUND, TYPE_NONE, 4 },  // 51 ground
  { "MEOWTH", 53, 28, R_COMUN, 0x8C4D, 40, 45, 35, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 52 normal
  { "PERSIAN", 0, 0, R_EVO, 0x8C4D, 65, 70, 60, 115, TYPE_NORMAL, TYPE_NONE, 0 },  // 53 normal
  { "PSYDUCK", 55, 33, R_COMUN, 0x4C98, 50, 52, 48, 55, TYPE_WATER, TYPE_NONE, 1 },  // 54 water
  { "GOLDUCK", 0, 0, R_EVO, 0x4C98, 80, 82, 78, 85, TYPE_WATER, TYPE_NONE, 1 },  // 55 water
  { "MANKEY", 57, 28, R_COMUN, 0xA2A5, 40, 80, 35, 70, TYPE_FIGHTING, TYPE_NONE, 0 },  // 56 fighting
  { "PRIMEAPE", 0, 0, R_EVO, 0xA2A5, 65, 105, 60, 95, TYPE_FIGHTING, TYPE_NONE, 0 },  // 57 fighting
  { "GROWLITHE", 59, 30, R_RARO, 0xEA87, 55, 70, 45, 60, TYPE_FIRE, TYPE_NONE, 3 },  // 58 fire
  { "ARCANINE", 0, 0, R_EVO, 0xEA87, 90, 110, 80, 95, TYPE_FIRE, TYPE_NONE, 3 },  // 59 fire
  { "POLIWAG", 61, 25, R_COMUN, 0x4C98, 40, 50, 40, 90, TYPE_WATER, TYPE_NONE, 1 },  // 60 water
  { "POLIWHIRL", 62, 36, R_EVO, 0x4C98, 65, 65, 65, 90, TYPE_WATER, TYPE_NONE, 1 },  // 61 water
  { "POLIWRATH", 0, 0, R_EVO, 0x4C98, 90, 95, 95, 70, TYPE_WATER, TYPE_FIGHTING, 1 },  // 62 water/fighting
  { "ABRA", 64, 16, R_COMUN, 0xD28F, 25, 20, 15, 90, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 63 psychic
  { "KADABRA", 65, 40, R_EVO, 0xD28F, 40, 35, 30, 105, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 64 psychic
  { "ALAKAZAM", 0, 0, R_EVO, 0xD28F, 55, 50, 45, 120, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 65 psychic
  { "MACHOP", 67, 28, R_COMUN, 0xA2A5, 70, 80, 50, 35, TYPE_FIGHTING, TYPE_NONE, 0 },  // 66 fighting
  { "MACHOKE", 68, 40, R_EVO, 0xA2A5, 80, 100, 70, 45, TYPE_FIGHTING, TYPE_NONE, 0 },  // 67 fighting
  { "MACHAMP", 0, 0, R_EVO, 0xA2A5, 90, 130, 80, 55, TYPE_FIGHTING, TYPE_NONE, 0 },  // 68 fighting
  { "BELLSPROUT", 70, 21, R_COMUN, 0x3C49, 50, 75, 35, 40, TYPE_GRASS, TYPE_POISON, 2 },  // 69 grass/poison
  { "WEEPINBELL", 71, 36, R_EVO, 0x3C49, 65, 90, 50, 55, TYPE_GRASS, TYPE_POISON, 2 },  // 70 grass/poison
  { "VICTREEBEL", 0, 0, R_EVO, 0x3C49, 80, 105, 65, 70, TYPE_GRASS, TYPE_POISON, 2 },  // 71 grass/poison
  { "TENTACOOL", 73, 30, R_COMUN, 0x4C98, 40, 40, 35, 70, TYPE_WATER, TYPE_POISON, 1 },  // 72 water/poison
  { "TENTACRUEL", 0, 0, R_EVO, 0x4C98, 80, 70, 65, 100, TYPE_WATER, TYPE_POISON, 1 },  // 73 water/poison
  { "GEODUDE", 75, 25, R_COMUN, 0x9407, 40, 80, 100, 20, TYPE_ROCK, TYPE_GROUND, 4 },  // 74 rock/ground
  { "GRAVELER", 76, 40, R_EVO, 0x9407, 55, 95, 115, 35, TYPE_ROCK, TYPE_GROUND, 4 },  // 75 rock/ground
  { "GOLEM", 0, 0, R_EVO, 0x9407, 80, 120, 130, 45, TYPE_ROCK, TYPE_GROUND, 4 },  // 76 rock/ground
  { "PONYTA", 78, 40, R_RARO, 0xEA87, 50, 85, 55, 90, TYPE_FIRE, TYPE_NONE, 3 },  // 77 fire
  { "RAPIDASH", 0, 0, R_EVO, 0xEA87, 65, 100, 70, 105, TYPE_FIRE, TYPE_NONE, 3 },  // 78 fire
  { "SLOWPOKE", 80, 37, R_COMUN, 0x4C98, 90, 65, 65, 15, TYPE_WATER, TYPE_PSYCHIC, 1 },  // 79 water/psychic
  { "SLOWBRO", 0, 0, R_EVO, 0x4C98, 95, 75, 110, 30, TYPE_WATER, TYPE_PSYCHIC, 1 },  // 80 water/psychic
  { "MAGNEMITE", 82, 30, R_COMUN, 0xBCA1, 25, 35, 70, 45, TYPE_ELECTRIC, TYPE_STEEL, 0 },  // 81 electric/steel
  { "MAGNETON", 0, 0, R_EVO, 0xBCA1, 50, 60, 95, 70, TYPE_ELECTRIC, TYPE_STEEL, 0 },  // 82 electric/steel
  { "FARFETCHD", 0, 0, R_RARO, 0x8C4D, 52, 90, 55, 60, TYPE_NORMAL, TYPE_FLYING, 0 },  // 83 normal/flying
  { "DODUO", 85, 31, R_COMUN, 0x8C4D, 35, 85, 45, 75, TYPE_NORMAL, TYPE_FLYING, 0 },  // 84 normal/flying
  { "DODRIO", 0, 0, R_EVO, 0x8C4D, 60, 110, 70, 110, TYPE_NORMAL, TYPE_FLYING, 0 },  // 85 normal/flying
  { "SEEL", 87, 34, R_COMUN, 0x4C98, 65, 45, 55, 45, TYPE_WATER, TYPE_NONE, 1 },  // 86 water
  { "DEWGONG", 0, 0, R_EVO, 0x4C98, 90, 70, 80, 70, TYPE_WATER, TYPE_ICE, 1 },  // 87 water/ice
  { "GRIMER", 89, 38, R_RARO, 0x8A73, 80, 80, 50, 25, TYPE_POISON, TYPE_NONE, 0 },  // 88 poison
  { "MUK", 0, 0, R_EVO, 0x8A73, 105, 105, 75, 50, TYPE_POISON, TYPE_NONE, 0 },  // 89 poison
  { "SHELLDER", 91, 30, R_COMUN, 0x4C98, 30, 65, 100, 40, TYPE_WATER, TYPE_NONE, 1 },  // 90 water
  { "CLOYSTER", 0, 0, R_EVO, 0x4C98, 50, 95, 180, 70, TYPE_WATER, TYPE_ICE, 1 },  // 91 water/ice
  { "GASTLY", 93, 25, R_COMUN, 0x6AD3, 30, 35, 30, 80, TYPE_GHOST, TYPE_POISON, 0 },  // 92 ghost/poison
  { "HAUNTER", 94, 40, R_EVO, 0x6AD3, 45, 50, 45, 95, TYPE_GHOST, TYPE_POISON, 0 },  // 93 ghost/poison
  { "GENGAR", 0, 0, R_EVO, 0x6AD3, 60, 65, 60, 110, TYPE_GHOST, TYPE_POISON, 0 },  // 94 ghost/poison
  { "ONIX", 0, 0, R_RARO, 0x9407, 35, 45, 160, 70, TYPE_ROCK, TYPE_GROUND, 4 },  // 95 rock/ground
  { "DROWZEE", 97, 26, R_COMUN, 0xD28F, 60, 48, 45, 42, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 96 psychic
  { "HYPNO", 0, 0, R_EVO, 0xD28F, 85, 73, 70, 67, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 97 psychic
  { "KRABBY", 99, 28, R_COMUN, 0x4C98, 30, 105, 90, 50, TYPE_WATER, TYPE_NONE, 1 },  // 98 water
  { "KINGLER", 0, 0, R_EVO, 0x4C98, 55, 130, 115, 75, TYPE_WATER, TYPE_NONE, 1 },  // 99 water
  { "VOLTORB", 101, 30, R_COMUN, 0xBCA1, 40, 30, 50, 100, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 100 electric
  { "ELECTRODE", 0, 0, R_EVO, 0xBCA1, 60, 50, 70, 150, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 101 electric
  { "EXEGGCUTE", 103, 30, R_COMUN, 0x3C49, 60, 40, 80, 40, TYPE_GRASS, TYPE_PSYCHIC, 2 },  // 102 grass/psychic
  { "EXEGGUTOR", 0, 0, R_EVO, 0x3C49, 95, 95, 85, 55, TYPE_GRASS, TYPE_PSYCHIC, 2 },  // 103 grass/psychic
  { "CUBONE", 105, 28, R_COMUN, 0xB447, 50, 50, 95, 35, TYPE_GROUND, TYPE_NONE, 4 },  // 104 ground
  { "MAROWAK", 0, 0, R_EVO, 0xB447, 60, 80, 110, 45, TYPE_GROUND, TYPE_NONE, 4 },  // 105 ground
  { "HITMONLEE", 0, 0, R_EVO, 0xA2A5, 50, 120, 53, 87, TYPE_FIGHTING, TYPE_NONE, 0 },  // 106 fighting
  { "HITMONCHAN", 0, 0, R_EVO, 0xA2A5, 50, 105, 79, 76, TYPE_FIGHTING, TYPE_NONE, 0 },  // 107 fighting
  { "LICKITUNG", 0, 0, R_RARO, 0x8C4D, 90, 55, 75, 30, TYPE_NORMAL, TYPE_NONE, 0 },  // 108 normal
  { "KOFFING", 110, 35, R_COMUN, 0x8A73, 40, 65, 95, 35, TYPE_POISON, TYPE_NONE, 0 },  // 109 poison
  { "WEEZING", 0, 0, R_EVO, 0x8A73, 65, 90, 120, 60, TYPE_POISON, TYPE_NONE, 0 },  // 110 poison
  { "RHYHORN", 112, 42, R_RARO, 0xB447, 80, 85, 95, 25, TYPE_GROUND, TYPE_ROCK, 4 },  // 111 ground/rock
  { "RHYDON", 0, 0, R_EVO, 0xB447, 105, 130, 120, 40, TYPE_GROUND, TYPE_ROCK, 4 },  // 112 ground/rock
  { "CHANSEY", 0, 0, R_RARO, 0x8C4D, 250, 5, 5, 50, TYPE_NORMAL, TYPE_NONE, 0 },  // 113 normal
  { "TANGELA", 0, 0, R_RARO, 0x3C49, 65, 55, 115, 60, TYPE_GRASS, TYPE_NONE, 2 },  // 114 grass
  { "KANGASKHAN", 0, 0, R_RARO, 0x8C4D, 105, 95, 80, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 115 normal
  { "HORSEA", 117, 32, R_COMUN, 0x4C98, 30, 40, 70, 60, TYPE_WATER, TYPE_NONE, 1 },  // 116 water
  { "SEADRA", 0, 0, R_EVO, 0x4C98, 55, 65, 95, 85, TYPE_WATER, TYPE_NONE, 1 },  // 117 water
  { "GOLDEEN", 119, 33, R_COMUN, 0x4C98, 45, 67, 60, 63, TYPE_WATER, TYPE_NONE, 1 },  // 118 water
  { "SEAKING", 0, 0, R_EVO, 0x4C98, 80, 92, 65, 68, TYPE_WATER, TYPE_NONE, 1 },  // 119 water
  { "STARYU", 121, 30, R_COMUN, 0x4C98, 30, 45, 55, 85, TYPE_WATER, TYPE_NONE, 1 },  // 120 water
  { "STARMIE", 0, 0, R_EVO, 0x4C98, 60, 75, 85, 115, TYPE_WATER, TYPE_PSYCHIC, 1 },  // 121 water/psychic
  { "MR. MIME", 0, 0, R_RARO, 0xD28F, 40, 45, 65, 90, TYPE_PSYCHIC, TYPE_FAIRY, 0 },  // 122 psychic/fairy
  { "SCYTHER", 0, 0, R_RARO, 0x7CC4, 70, 110, 80, 105, TYPE_BUG, TYPE_FLYING, 2 },  // 123 bug/flying
  { "JYNX", 0, 0, R_EVO, 0x4DB8, 65, 50, 35, 95, TYPE_ICE, TYPE_PSYCHIC, 5 },  // 124 ice/psychic
  { "ELECTABUZZ", 0, 0, R_EVO, 0xBCA1, 65, 83, 57, 105, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 125 electric
  { "MAGMAR", 0, 0, R_EVO, 0xEA87, 65, 95, 57, 93, TYPE_FIRE, TYPE_NONE, 3 },  // 126 fire
  { "PINSIR", 0, 0, R_RARO, 0x7CC4, 65, 125, 100, 85, TYPE_BUG, TYPE_NONE, 2 },  // 127 bug
  { "TAUROS", 0, 0, R_RARO, 0x8C4D, 75, 100, 95, 110, TYPE_NORMAL, TYPE_NONE, 0 },  // 128 normal
  { "MAGIKARP", 130, 20, R_COMUN, 0x4C98, 20, 10, 55, 80, TYPE_WATER, TYPE_NONE, 1 },  // 129 water
  { "GYARADOS", 0, 0, R_EVO, 0x4C98, 95, 125, 79, 81, TYPE_WATER, TYPE_FLYING, 1 },  // 130 water/flying
  { "LAPRAS", 0, 0, R_RARO, 0x4C98, 130, 85, 80, 60, TYPE_WATER, TYPE_ICE, 1 },  // 131 water/ice
  { "DITTO", 0, 0, R_RARO, 0x8C4D, 48, 48, 48, 48, TYPE_NORMAL, TYPE_NONE, 0 },  // 132 normal
  { "EEVEE", 134, 30, R_COMUN, 0x8C4D, 55, 55, 50, 55, TYPE_NORMAL, TYPE_NONE, 0 },  // 133 normal
  { "VAPOREON", 0, 0, R_EVO, 0x4C98, 130, 65, 60, 65, TYPE_WATER, TYPE_NONE, 1 },  // 134 water
  { "JOLTEON", 0, 0, R_EVO, 0xBCA1, 65, 65, 60, 130, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 135 electric
  { "FLAREON", 0, 0, R_EVO, 0xEA87, 65, 130, 60, 65, TYPE_FIRE, TYPE_NONE, 3 },  // 136 fire
  { "PORYGON", 0, 0, R_RARO, 0x8C4D, 65, 60, 70, 40, TYPE_NORMAL, TYPE_NONE, 0 },  // 137 normal
  { "OMANYTE", 139, 40, R_RARO, 0x9407, 35, 40, 100, 35, TYPE_ROCK, TYPE_WATER, 1 },  // 138 rock/water
  { "OMASTAR", 0, 0, R_EVO, 0x9407, 70, 60, 125, 55, TYPE_ROCK, TYPE_WATER, 1 },  // 139 rock/water
  { "KABUTO", 141, 40, R_RARO, 0x9407, 30, 80, 90, 55, TYPE_ROCK, TYPE_WATER, 1 },  // 140 rock/water
  { "KABUTOPS", 0, 0, R_EVO, 0x9407, 60, 115, 105, 80, TYPE_ROCK, TYPE_WATER, 1 },  // 141 rock/water
  { "AERODACTYL", 0, 0, R_RARO, 0x9407, 80, 105, 65, 130, TYPE_ROCK, TYPE_FLYING, 4 },  // 142 rock/flying
  { "SNORLAX", 0, 0, R_RARO, 0x8C4D, 160, 110, 65, 30, TYPE_NORMAL, TYPE_NONE, 0 },  // 143 normal
  { "ARTICUNO", 0, 0, R_LEGENDARIO, 0x4DB8, 90, 85, 100, 85, TYPE_ICE, TYPE_FLYING, 5 },  // 144 ice/flying
  { "ZAPDOS", 0, 0, R_LEGENDARIO, 0xBCA1, 90, 90, 85, 100, TYPE_ELECTRIC, TYPE_FLYING, 0 },  // 145 electric/flying
  { "MOLTRES", 0, 0, R_LEGENDARIO, 0xEA87, 90, 100, 90, 90, TYPE_FIRE, TYPE_FLYING, 3 },  // 146 fire/flying
  { "DRATINI", 148, 30, R_RARO, 0x5A98, 41, 64, 45, 50, TYPE_DRAGON, TYPE_NONE, 1 },  // 147 dragon
  { "DRAGONAIR", 149, 55, R_EVO, 0x5A98, 61, 84, 65, 70, TYPE_DRAGON, TYPE_NONE, 1 },  // 148 dragon
  { "DRAGONITE", 0, 0, R_EVO, 0x5A98, 91, 134, 95, 80, TYPE_DRAGON, TYPE_FLYING, 1 },  // 149 dragon/flying
  { "MEWTWO", 0, 0, R_LEGENDARIO, 0xD28F, 106, 110, 90, 130, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 150 psychic
  { "MEW", 0, 0, R_LEGENDARIO, 0xD28F, 100, 100, 100, 100, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 151 psychic
  { "CHIKORITA", 153, 16, R_COMUN, 0x3C49, 45, 49, 65, 45, TYPE_GRASS, TYPE_NONE, 2 },  // 152 grass
  { "BAYLEEF", 154, 32, R_EVO, 0x3C49, 60, 62, 80, 60, TYPE_GRASS, TYPE_NONE, 2 },  // 153 grass
  { "MEGANIUM", 0, 0, R_EVO, 0x3C49, 80, 82, 100, 80, TYPE_GRASS, TYPE_NONE, 2 },  // 154 grass
  { "CYNDAQUIL", 156, 14, R_COMUN, 0xEA87, 39, 52, 43, 65, TYPE_FIRE, TYPE_NONE, 3 },  // 155 fire
  { "QUILAVA", 157, 36, R_EVO, 0xEA87, 58, 64, 58, 80, TYPE_FIRE, TYPE_NONE, 3 },  // 156 fire
  { "TYPHLOSION", 0, 0, R_EVO, 0xEA87, 78, 84, 78, 100, TYPE_FIRE, TYPE_NONE, 3 },  // 157 fire
  { "TOTODILE", 159, 18, R_COMUN, 0x4C98, 50, 65, 64, 43, TYPE_WATER, TYPE_NONE, 1 },  // 158 water
  { "CROCONAW", 160, 30, R_EVO, 0x4C98, 65, 80, 80, 58, TYPE_WATER, TYPE_NONE, 1 },  // 159 water
  { "FERALIGATR", 0, 0, R_EVO, 0x4C98, 85, 105, 100, 78, TYPE_WATER, TYPE_NONE, 1 },  // 160 water
  { "SENTRET", 162, 15, R_COMUN, 0x8C4D, 35, 46, 34, 20, TYPE_NORMAL, TYPE_NONE, 0 },  // 161 normal
  { "FURRET", 0, 0, R_EVO, 0x8C4D, 85, 76, 64, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 162 normal
  { "HOOTHOOT", 164, 20, R_COMUN, 0x8C4D, 60, 30, 30, 50, TYPE_NORMAL, TYPE_FLYING, 0 },  // 163 normal/flying
  { "NOCTOWL", 0, 0, R_EVO, 0x8C4D, 100, 50, 50, 70, TYPE_NORMAL, TYPE_FLYING, 0 },  // 164 normal/flying
  { "LEDYBA", 166, 18, R_COMUN, 0x7CC4, 40, 20, 30, 55, TYPE_BUG, TYPE_FLYING, 2 },  // 165 bug/flying
  { "LEDIAN", 0, 0, R_EVO, 0x7CC4, 55, 35, 50, 85, TYPE_BUG, TYPE_FLYING, 2 },  // 166 bug/flying
  { "SPINARAK", 168, 22, R_COMUN, 0x7CC4, 40, 60, 40, 30, TYPE_BUG, TYPE_POISON, 2 },  // 167 bug/poison
  { "ARIADOS", 0, 0, R_EVO, 0x7CC4, 70, 90, 70, 40, TYPE_BUG, TYPE_POISON, 2 },  // 168 bug/poison
  { "CROBAT", 0, 0, R_EVO, 0x8A73, 85, 90, 80, 130, TYPE_POISON, TYPE_FLYING, 0 },  // 169 poison/flying
  { "CHINCHOU", 171, 27, R_COMUN, 0x4C98, 75, 38, 38, 67, TYPE_WATER, TYPE_ELECTRIC, 1 },  // 170 water/electric
  { "LANTURN", 0, 0, R_EVO, 0x4C98, 125, 58, 58, 67, TYPE_WATER, TYPE_ELECTRIC, 1 },  // 171 water/electric
  { "PICHU", 25, 10, R_COMUN, 0xBCA1, 20, 40, 15, 60, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 172 electric
  { "CLEFFA", 35, 10, R_COMUN, 0x8C4D, 50, 25, 28, 15, TYPE_FAIRY, TYPE_NONE, 0 },  // 173 fairy
  { "IGGLYBUFF", 39, 10, R_COMUN, 0x8C4D, 90, 30, 15, 15, TYPE_NORMAL, TYPE_FAIRY, 0 },  // 174 normal/fairy
  { "TOGEPI", 176, 10, R_RARO, 0x8C4D, 35, 20, 65, 20, TYPE_FAIRY, TYPE_NONE, 0 },  // 175 fairy
  { "TOGETIC", 0, 0, R_EVO, 0x8C4D, 55, 40, 85, 40, TYPE_FAIRY, TYPE_FLYING, 0 },  // 176 fairy/flying
  { "NATU", 178, 25, R_COMUN, 0xD28F, 40, 50, 45, 70, TYPE_PSYCHIC, TYPE_FLYING, 0 },  // 177 psychic/flying
  { "XATU", 0, 0, R_EVO, 0xD28F, 65, 75, 70, 95, TYPE_PSYCHIC, TYPE_FLYING, 0 },  // 178 psychic/flying
  { "MAREEP", 180, 15, R_COMUN, 0xBCA1, 55, 40, 40, 35, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 179 electric
  { "FLAAFFY", 181, 30, R_EVO, 0xBCA1, 70, 55, 55, 45, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 180 electric
  { "AMPHAROS", 0, 0, R_EVO, 0xBCA1, 90, 75, 85, 55, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 181 electric
  { "BELLOSSOM", 0, 0, R_EVO, 0x3C49, 75, 80, 95, 50, TYPE_GRASS, TYPE_NONE, 2 },  // 182 grass
  { "MARILL", 184, 18, R_EVO, 0x4C98, 70, 20, 50, 40, TYPE_WATER, TYPE_FAIRY, 1 },  // 183 water/fairy
  { "AZUMARILL", 0, 0, R_EVO, 0x4C98, 100, 50, 80, 50, TYPE_WATER, TYPE_FAIRY, 1 },  // 184 water/fairy
  { "SUDOWOODO", 0, 0, R_COMUN, 0x9407, 70, 100, 115, 30, TYPE_ROCK, TYPE_NONE, 4 },  // 185 rock
  { "POLITOED", 0, 0, R_EVO, 0x4C98, 90, 75, 75, 70, TYPE_WATER, TYPE_NONE, 1 },  // 186 water
  { "HOPPIP", 188, 18, R_COMUN, 0x3C49, 35, 35, 40, 50, TYPE_GRASS, TYPE_FLYING, 2 },  // 187 grass/flying
  { "SKIPLOOM", 189, 27, R_EVO, 0x3C49, 55, 45, 50, 80, TYPE_GRASS, TYPE_FLYING, 2 },  // 188 grass/flying
  { "JUMPLUFF", 0, 0, R_EVO, 0x3C49, 75, 55, 70, 110, TYPE_GRASS, TYPE_FLYING, 2 },  // 189 grass/flying
  { "AIPOM", 0, 0, R_COMUN, 0x8C4D, 55, 70, 55, 85, TYPE_NORMAL, TYPE_NONE, 0 },  // 190 normal
  { "SUNKERN", 192, 20, R_COMUN, 0x3C49, 30, 30, 30, 30, TYPE_GRASS, TYPE_NONE, 2 },  // 191 grass
  { "SUNFLORA", 0, 0, R_EVO, 0x3C49, 75, 75, 55, 30, TYPE_GRASS, TYPE_NONE, 2 },  // 192 grass
  { "YANMA", 0, 0, R_RARO, 0x7CC4, 65, 65, 45, 95, TYPE_BUG, TYPE_FLYING, 2 },  // 193 bug/flying
  { "WOOPER", 195, 20, R_COMUN, 0x4C98, 55, 45, 45, 15, TYPE_WATER, TYPE_GROUND, 1 },  // 194 water/ground
  { "QUAGSIRE", 0, 0, R_EVO, 0x4C98, 95, 85, 85, 35, TYPE_WATER, TYPE_GROUND, 1 },  // 195 water/ground
  { "ESPEON", 0, 0, R_EVO, 0xD28F, 65, 65, 60, 110, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 196 psychic
  { "UMBREON", 0, 0, R_EVO, 0x5A6E, 95, 65, 110, 65, TYPE_DARK, TYPE_NONE, 0 },  // 197 dark
  { "MURKROW", 0, 0, R_RARO, 0x5A6E, 60, 85, 42, 91, TYPE_DARK, TYPE_FLYING, 0 },  // 198 dark/flying
  { "SLOWKING", 0, 0, R_EVO, 0x4C98, 95, 75, 80, 30, TYPE_WATER, TYPE_PSYCHIC, 1 },  // 199 water/psychic
  { "MISDREAVUS", 0, 0, R_RARO, 0x6AD3, 60, 60, 60, 85, TYPE_GHOST, TYPE_NONE, 0 },  // 200 ghost
  { "UNOWN", 0, 0, R_RARO, 0xD28F, 48, 72, 48, 48, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 201 psychic
  { "WOBBUFFET", 0, 0, R_EVO, 0xD28F, 190, 33, 58, 33, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 202 psychic
  { "GIRAFARIG", 0, 0, R_COMUN, 0x8C4D, 70, 80, 65, 85, TYPE_NORMAL, TYPE_PSYCHIC, 0 },  // 203 normal/psychic
  { "PINECO", 205, 31, R_COMUN, 0x7CC4, 50, 65, 90, 15, TYPE_BUG, TYPE_NONE, 2 },  // 204 bug
  { "FORRETRESS", 0, 0, R_EVO, 0x7CC4, 75, 90, 140, 40, TYPE_BUG, TYPE_STEEL, 2 },  // 205 bug/steel
  { "DUNSPARCE", 0, 0, R_RARO, 0x8C4D, 100, 70, 70, 45, TYPE_NORMAL, TYPE_NONE, 0 },  // 206 normal
  { "GLIGAR", 0, 0, R_COMUN, 0xB447, 65, 75, 105, 85, TYPE_GROUND, TYPE_FLYING, 4 },  // 207 ground/flying
  { "STEELIX", 0, 0, R_EVO, 0xB447, 75, 85, 200, 30, TYPE_STEEL, TYPE_GROUND, 4 },  // 208 steel/ground
  { "SNUBBULL", 210, 23, R_COMUN, 0x8C4D, 60, 80, 50, 30, TYPE_FAIRY, TYPE_NONE, 0 },  // 209 fairy
  { "GRANBULL", 0, 0, R_EVO, 0x8C4D, 90, 120, 75, 45, TYPE_FAIRY, TYPE_NONE, 0 },  // 210 fairy
  { "QWILFISH", 0, 0, R_COMUN, 0x4C98, 65, 95, 85, 85, TYPE_WATER, TYPE_POISON, 1 },  // 211 water/poison
  { "SCIZOR", 0, 0, R_EVO, 0x7CC4, 70, 130, 100, 65, TYPE_BUG, TYPE_STEEL, 2 },  // 212 bug/steel
  { "SHUCKLE", 0, 0, R_RARO, 0x7CC4, 20, 10, 230, 5, TYPE_BUG, TYPE_ROCK, 2 },  // 213 bug/rock
  { "HERACROSS", 0, 0, R_RARO, 0x7CC4, 80, 125, 75, 85, TYPE_BUG, TYPE_FIGHTING, 2 },  // 214 bug/fighting
  { "SNEASEL", 0, 0, R_RARO, 0x5A6E, 55, 95, 55, 115, TYPE_DARK, TYPE_ICE, 0 },  // 215 dark/ice
  { "TEDDIURSA", 217, 30, R_COMUN, 0x8C4D, 60, 80, 50, 40, TYPE_NORMAL, TYPE_NONE, 0 },  // 216 normal
  { "URSARING", 0, 0, R_EVO, 0x8C4D, 90, 130, 75, 55, TYPE_NORMAL, TYPE_NONE, 0 },  // 217 normal
  { "SLUGMA", 219, 38, R_COMUN, 0xEA87, 40, 40, 40, 20, TYPE_FIRE, TYPE_NONE, 3 },  // 218 fire
  { "MAGCARGO", 0, 0, R_EVO, 0xEA87, 60, 50, 120, 30, TYPE_FIRE, TYPE_ROCK, 3 },  // 219 fire/rock
  { "SWINUB", 221, 33, R_COMUN, 0x4DB8, 50, 50, 40, 50, TYPE_ICE, TYPE_GROUND, 5 },  // 220 ice/ground
  { "PILOSWINE", 0, 0, R_EVO, 0x4DB8, 100, 100, 80, 50, TYPE_ICE, TYPE_GROUND, 5 },  // 221 ice/ground
  { "CORSOLA", 0, 0, R_RARO, 0x4C98, 65, 55, 95, 35, TYPE_WATER, TYPE_ROCK, 1 },  // 222 water/rock
  { "REMORAID", 224, 25, R_COMUN, 0x4C98, 35, 65, 35, 65, TYPE_WATER, TYPE_NONE, 1 },  // 223 water
  { "OCTILLERY", 0, 0, R_EVO, 0x4C98, 75, 105, 75, 45, TYPE_WATER, TYPE_NONE, 1 },  // 224 water
  { "DELIBIRD", 0, 0, R_RARO, 0x4DB8, 45, 55, 45, 75, TYPE_ICE, TYPE_FLYING, 5 },  // 225 ice/flying
  { "MANTINE", 0, 0, R_RARO, 0x4C98, 85, 40, 70, 70, TYPE_WATER, TYPE_FLYING, 1 },  // 226 water/flying
  { "SKARMORY", 0, 0, R_RARO, 0x7C73, 65, 80, 140, 70, TYPE_STEEL, TYPE_FLYING, 4 },  // 227 steel/flying
  { "HOUNDOUR", 229, 24, R_COMUN, 0x5A6E, 45, 60, 30, 65, TYPE_DARK, TYPE_FIRE, 0 },  // 228 dark/fire
  { "HOUNDOOM", 0, 0, R_EVO, 0x5A6E, 75, 90, 50, 95, TYPE_DARK, TYPE_FIRE, 0 },  // 229 dark/fire
  { "KINGDRA", 0, 0, R_EVO, 0x4C98, 75, 95, 95, 85, TYPE_WATER, TYPE_DRAGON, 1 },  // 230 water/dragon
  { "PHANPY", 232, 25, R_COMUN, 0xB447, 90, 60, 60, 40, TYPE_GROUND, TYPE_NONE, 4 },  // 231 ground
  { "DONPHAN", 0, 0, R_EVO, 0xB447, 90, 120, 120, 50, TYPE_GROUND, TYPE_NONE, 4 },  // 232 ground
  { "PORYGON2", 0, 0, R_EVO, 0x8C4D, 85, 80, 90, 60, TYPE_NORMAL, TYPE_NONE, 0 },  // 233 normal
  { "STANTLER", 0, 0, R_RARO, 0x8C4D, 73, 95, 62, 85, TYPE_NORMAL, TYPE_NONE, 0 },  // 234 normal
  { "SMEARGLE", 0, 0, R_RARO, 0x8C4D, 55, 20, 35, 75, TYPE_NORMAL, TYPE_NONE, 0 },  // 235 normal
  { "TYROGUE", 0, 0, R_RARO, 0xA2A5, 35, 35, 35, 35, TYPE_FIGHTING, TYPE_NONE, 0 },  // 236 fighting
  { "HITMONTOP", 0, 0, R_EVO, 0xA2A5, 50, 95, 95, 70, TYPE_FIGHTING, TYPE_NONE, 0 },  // 237 fighting
  { "SMOOCHUM", 124, 30, R_RARO, 0x4DB8, 45, 30, 15, 65, TYPE_ICE, TYPE_PSYCHIC, 5 },  // 238 ice/psychic
  { "ELEKID", 125, 30, R_RARO, 0xBCA1, 45, 63, 37, 95, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 239 electric
  { "MAGBY", 126, 30, R_RARO, 0xEA87, 45, 75, 37, 83, TYPE_FIRE, TYPE_NONE, 3 },  // 240 fire
  { "MILTANK", 0, 0, R_RARO, 0x8C4D, 95, 80, 105, 100, TYPE_NORMAL, TYPE_NONE, 0 },  // 241 normal
  { "BLISSEY", 0, 0, R_EVO, 0x8C4D, 255, 10, 10, 55, TYPE_NORMAL, TYPE_NONE, 0 },  // 242 normal
  { "RAIKOU", 0, 0, R_LEGENDARIO, 0xBCA1, 90, 85, 75, 115, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 243 electric
  { "ENTEI", 0, 0, R_LEGENDARIO, 0xEA87, 115, 115, 85, 100, TYPE_FIRE, TYPE_NONE, 3 },  // 244 fire
  { "SUICUNE", 0, 0, R_LEGENDARIO, 0x4C98, 100, 75, 115, 85, TYPE_WATER, TYPE_NONE, 1 },  // 245 water
  { "LARVITAR", 247, 30, R_RARO, 0x9407, 50, 64, 50, 41, TYPE_ROCK, TYPE_GROUND, 4 },  // 246 rock/ground
  { "PUPITAR", 248, 55, R_EVO, 0x9407, 70, 84, 70, 51, TYPE_ROCK, TYPE_GROUND, 4 },  // 247 rock/ground
  { "TYRANITAR", 0, 0, R_EVO, 0x9407, 100, 134, 110, 61, TYPE_ROCK, TYPE_DARK, 4 },  // 248 rock/dark
  { "LUGIA", 0, 0, R_LEGENDARIO, 0xD28F, 106, 90, 130, 110, TYPE_PSYCHIC, TYPE_FLYING, 0 },  // 249 psychic/flying
  { "HO_OH", 0, 0, R_LEGENDARIO, 0xEA87, 106, 130, 90, 90, TYPE_FIRE, TYPE_FLYING, 3 },  // 250 fire/flying
  { "CELEBI", 0, 0, R_LEGENDARIO, 0xD28F, 100, 100, 100, 100, TYPE_PSYCHIC, TYPE_GRASS, 0 },  // 251 psychic/grass
  { "TREECKO", 253, 16, R_COMUN, 0x3C49, 40, 45, 35, 70, TYPE_GRASS, TYPE_NONE, 2 },  // 252 grass
  { "GROVYLE", 254, 36, R_EVO, 0x3C49, 50, 65, 45, 95, TYPE_GRASS, TYPE_NONE, 2 },  // 253 grass
  { "SCEPTILE", 0, 0, R_EVO, 0x3C49, 70, 85, 65, 120, TYPE_GRASS, TYPE_NONE, 2 },  // 254 grass
  { "TORCHIC", 256, 16, R_COMUN, 0xEA87, 45, 60, 40, 45, TYPE_FIRE, TYPE_NONE, 3 },  // 255 fire
  { "COMBUSKEN", 257, 36, R_EVO, 0xEA87, 60, 85, 60, 55, TYPE_FIRE, TYPE_FIGHTING, 3 },  // 256 fire/fighting
  { "BLAZIKEN", 0, 0, R_EVO, 0xEA87, 80, 120, 70, 80, TYPE_FIRE, TYPE_FIGHTING, 3 },  // 257 fire/fighting
  { "MUDKIP", 259, 16, R_COMUN, 0x4C98, 50, 70, 50, 40, TYPE_WATER, TYPE_NONE, 1 },  // 258 water
  { "MARSHTOMP", 260, 36, R_EVO, 0x4C98, 70, 85, 70, 50, TYPE_WATER, TYPE_GROUND, 1 },  // 259 water/ground
  { "SWAMPERT", 0, 0, R_EVO, 0x4C98, 100, 110, 90, 60, TYPE_WATER, TYPE_GROUND, 1 },  // 260 water/ground
  { "POOCHYENA", 262, 18, R_COMUN, 0x5A6E, 35, 55, 35, 35, TYPE_DARK, TYPE_NONE, 0 },  // 261 dark
  { "MIGHTYENA", 0, 0, R_EVO, 0x5A6E, 70, 90, 70, 70, TYPE_DARK, TYPE_NONE, 0 },  // 262 dark
  { "ZIGZAGOON", 264, 20, R_COMUN, 0x8C4D, 38, 30, 41, 60, TYPE_NORMAL, TYPE_NONE, 0 },  // 263 normal
  { "LINOONE", 0, 0, R_EVO, 0x8C4D, 78, 70, 61, 100, TYPE_NORMAL, TYPE_NONE, 0 },  // 264 normal
  { "WURMPLE", 266, 7, R_COMUN, 0x7CC4, 45, 45, 35, 20, TYPE_BUG, TYPE_NONE, 2 },  // 265 bug
  { "SILCOON", 267, 10, R_EVO, 0x7CC4, 50, 35, 55, 15, TYPE_BUG, TYPE_NONE, 2 },  // 266 bug
  { "BEAUTIFLY", 0, 0, R_EVO, 0x7CC4, 60, 70, 50, 65, TYPE_BUG, TYPE_FLYING, 2 },  // 267 bug/flying
  { "CASCOON", 269, 10, R_EVO, 0x7CC4, 50, 35, 55, 15, TYPE_BUG, TYPE_NONE, 2 },  // 268 bug
  { "DUSTOX", 0, 0, R_EVO, 0x7CC4, 60, 50, 70, 65, TYPE_BUG, TYPE_POISON, 2 },  // 269 bug/poison
  { "LOTAD", 271, 14, R_COMUN, 0x4C98, 40, 30, 30, 30, TYPE_WATER, TYPE_GRASS, 1 },  // 270 water/grass
  { "LOMBRE", 272, 30, R_EVO, 0x4C98, 60, 50, 50, 50, TYPE_WATER, TYPE_GRASS, 1 },  // 271 water/grass
  { "LUDICOLO", 0, 0, R_EVO, 0x4C98, 80, 70, 70, 70, TYPE_WATER, TYPE_GRASS, 1 },  // 272 water/grass
  { "SEEDOT", 274, 14, R_COMUN, 0x3C49, 40, 40, 50, 30, TYPE_GRASS, TYPE_NONE, 2 },  // 273 grass
  { "NUZLEAF", 275, 30, R_EVO, 0x3C49, 70, 70, 40, 60, TYPE_GRASS, TYPE_DARK, 2 },  // 274 grass/dark
  { "SHIFTRY", 0, 0, R_EVO, 0x3C49, 90, 100, 60, 80, TYPE_GRASS, TYPE_DARK, 2 },  // 275 grass/dark
  { "TAILLOW", 277, 22, R_COMUN, 0x8C4D, 40, 55, 30, 85, TYPE_NORMAL, TYPE_FLYING, 0 },  // 276 normal/flying
  { "SWELLOW", 0, 0, R_EVO, 0x8C4D, 60, 85, 60, 125, TYPE_NORMAL, TYPE_FLYING, 0 },  // 277 normal/flying
  { "WINGULL", 279, 25, R_COMUN, 0x4C98, 40, 30, 30, 85, TYPE_WATER, TYPE_FLYING, 1 },  // 278 water/flying
  { "PELIPPER", 0, 0, R_EVO, 0x4C98, 60, 50, 100, 65, TYPE_WATER, TYPE_FLYING, 1 },  // 279 water/flying
  { "RALTS", 281, 20, R_COMUN, 0xD28F, 28, 25, 25, 40, TYPE_PSYCHIC, TYPE_FAIRY, 0 },  // 280 psychic/fairy
  { "KIRLIA", 282, 30, R_EVO, 0xD28F, 38, 35, 35, 50, TYPE_PSYCHIC, TYPE_FAIRY, 0 },  // 281 psychic/fairy
  { "GARDEVOIR", 0, 0, R_EVO, 0xD28F, 68, 65, 65, 80, TYPE_PSYCHIC, TYPE_FAIRY, 0 },  // 282 psychic/fairy
  { "SURSKIT", 284, 22, R_COMUN, 0x7CC4, 40, 30, 32, 65, TYPE_BUG, TYPE_WATER, 2 },  // 283 bug/water
  { "MASQUERAIN", 0, 0, R_EVO, 0x7CC4, 70, 60, 62, 80, TYPE_BUG, TYPE_FLYING, 2 },  // 284 bug/flying
  { "SHROOMISH", 286, 23, R_COMUN, 0x3C49, 60, 40, 60, 35, TYPE_GRASS, TYPE_NONE, 2 },  // 285 grass
  { "BRELOOM", 0, 0, R_EVO, 0x3C49, 60, 130, 80, 70, TYPE_GRASS, TYPE_FIGHTING, 2 },  // 286 grass/fighting
  { "SLAKOTH", 288, 18, R_COMUN, 0x8C4D, 60, 60, 60, 30, TYPE_NORMAL, TYPE_NONE, 0 },  // 287 normal
  { "VIGOROTH", 289, 36, R_EVO, 0x8C4D, 80, 80, 80, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 288 normal
  { "SLAKING", 0, 0, R_EVO, 0x8C4D, 150, 160, 100, 100, TYPE_NORMAL, TYPE_NONE, 0 },  // 289 normal
  { "NINCADA", 291, 20, R_COMUN, 0x7CC4, 31, 45, 90, 40, TYPE_BUG, TYPE_GROUND, 2 },  // 290 bug/ground
  { "NINJASK", 0, 0, R_EVO, 0x7CC4, 61, 90, 45, 160, TYPE_BUG, TYPE_FLYING, 2 },  // 291 bug/flying
  { "SHEDINJA", 0, 0, R_EVO, 0x7CC4, 1, 90, 45, 40, TYPE_BUG, TYPE_GHOST, 2 },  // 292 bug/ghost
  { "WHISMUR", 294, 20, R_COMUN, 0x8C4D, 64, 51, 23, 28, TYPE_NORMAL, TYPE_NONE, 0 },  // 293 normal
  { "LOUDRED", 295, 40, R_EVO, 0x8C4D, 84, 71, 43, 48, TYPE_NORMAL, TYPE_NONE, 0 },  // 294 normal
  { "EXPLOUD", 0, 0, R_EVO, 0x8C4D, 104, 91, 63, 68, TYPE_NORMAL, TYPE_NONE, 0 },  // 295 normal
  { "MAKUHITA", 297, 24, R_COMUN, 0xA2A5, 72, 60, 30, 25, TYPE_FIGHTING, TYPE_NONE, 0 },  // 296 fighting
  { "HARIYAMA", 0, 0, R_EVO, 0xA2A5, 144, 120, 60, 50, TYPE_FIGHTING, TYPE_NONE, 0 },  // 297 fighting
  { "AZURILL", 183, 10, R_COMUN, 0x8C4D, 50, 20, 40, 20, TYPE_NORMAL, TYPE_FAIRY, 0 },  // 298 normal/fairy
  { "NOSEPASS", 0, 0, R_COMUN, 0x9407, 30, 45, 135, 30, TYPE_ROCK, TYPE_NONE, 4 },  // 299 rock
  { "SKITTY", 301, 30, R_COMUN, 0x8C4D, 50, 45, 45, 50, TYPE_NORMAL, TYPE_NONE, 0 },  // 300 normal
  { "DELCATTY", 0, 0, R_EVO, 0x8C4D, 70, 65, 65, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 301 normal
  { "SABLEYE", 0, 0, R_RARO, 0x5A6E, 50, 75, 75, 50, TYPE_DARK, TYPE_GHOST, 0 },  // 302 dark/ghost
  { "MAWILE", 0, 0, R_RARO, 0x7C73, 50, 85, 85, 50, TYPE_STEEL, TYPE_FAIRY, 4 },  // 303 steel/fairy
  { "ARON", 305, 32, R_COMUN, 0x7C73, 50, 70, 100, 30, TYPE_STEEL, TYPE_ROCK, 4 },  // 304 steel/rock
  { "LAIRON", 306, 42, R_EVO, 0x7C73, 60, 90, 140, 40, TYPE_STEEL, TYPE_ROCK, 4 },  // 305 steel/rock
  { "AGGRON", 0, 0, R_EVO, 0x7C73, 70, 110, 180, 50, TYPE_STEEL, TYPE_ROCK, 4 },  // 306 steel/rock
  { "MEDITITE", 308, 37, R_COMUN, 0xA2A5, 30, 40, 55, 60, TYPE_FIGHTING, TYPE_PSYCHIC, 0 },  // 307 fighting/psychic
  { "MEDICHAM", 0, 0, R_EVO, 0xA2A5, 60, 60, 75, 80, TYPE_FIGHTING, TYPE_PSYCHIC, 0 },  // 308 fighting/psychic
  { "ELECTRIKE", 310, 26, R_COMUN, 0xBCA1, 40, 45, 40, 65, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 309 electric
  { "MANECTRIC", 0, 0, R_EVO, 0xBCA1, 70, 75, 60, 105, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 310 electric
  { "PLUSLE", 0, 0, R_COMUN, 0xBCA1, 60, 50, 40, 95, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 311 electric
  { "MINUN", 0, 0, R_COMUN, 0xBCA1, 60, 40, 50, 95, TYPE_ELECTRIC, TYPE_NONE, 0 },  // 312 electric
  { "VOLBEAT", 0, 0, R_COMUN, 0x7CC4, 65, 73, 75, 85, TYPE_BUG, TYPE_NONE, 2 },  // 313 bug
  { "ILLUMISE", 0, 0, R_COMUN, 0x7CC4, 65, 47, 75, 85, TYPE_BUG, TYPE_NONE, 2 },  // 314 bug
  { "ROSELIA", 0, 0, R_COMUN, 0x3C49, 50, 60, 45, 65, TYPE_GRASS, TYPE_POISON, 2 },  // 315 grass/poison
  { "GULPIN", 317, 26, R_COMUN, 0x8A73, 70, 43, 53, 40, TYPE_POISON, TYPE_NONE, 0 },  // 316 poison
  { "SWALOT", 0, 0, R_EVO, 0x8A73, 100, 73, 83, 55, TYPE_POISON, TYPE_NONE, 0 },  // 317 poison
  { "CARVANHA", 319, 30, R_COMUN, 0x4C98, 45, 90, 20, 65, TYPE_WATER, TYPE_DARK, 1 },  // 318 water/dark
  { "SHARPEDO", 0, 0, R_EVO, 0x4C98, 70, 120, 40, 95, TYPE_WATER, TYPE_DARK, 1 },  // 319 water/dark
  { "WAILMER", 321, 40, R_COMUN, 0x4C98, 130, 70, 35, 60, TYPE_WATER, TYPE_NONE, 1 },  // 320 water
  { "WAILORD", 0, 0, R_EVO, 0x4C98, 170, 90, 45, 60, TYPE_WATER, TYPE_NONE, 1 },  // 321 water
  { "NUMEL", 323, 33, R_COMUN, 0xEA87, 60, 60, 40, 35, TYPE_FIRE, TYPE_GROUND, 3 },  // 322 fire/ground
  { "CAMERUPT", 0, 0, R_EVO, 0xEA87, 70, 100, 70, 40, TYPE_FIRE, TYPE_GROUND, 3 },  // 323 fire/ground
  { "TORKOAL", 0, 0, R_RARO, 0xEA87, 70, 85, 140, 20, TYPE_FIRE, TYPE_NONE, 3 },  // 324 fire
  { "SPOINK", 326, 32, R_COMUN, 0xD28F, 60, 25, 35, 60, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 325 psychic
  { "GRUMPIG", 0, 0, R_EVO, 0xD28F, 80, 45, 65, 80, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 326 psychic
  { "SPINDA", 0, 0, R_RARO, 0x8C4D, 60, 60, 60, 60, TYPE_NORMAL, TYPE_NONE, 0 },  // 327 normal
  { "TRAPINCH", 329, 35, R_COMUN, 0xB447, 45, 100, 45, 10, TYPE_GROUND, TYPE_NONE, 4 },  // 328 ground
  { "VIBRAVA", 330, 45, R_EVO, 0xB447, 50, 70, 50, 70, TYPE_GROUND, TYPE_DRAGON, 4 },  // 329 ground/dragon
  { "FLYGON", 0, 0, R_EVO, 0xB447, 80, 100, 80, 100, TYPE_GROUND, TYPE_DRAGON, 4 },  // 330 ground/dragon
  { "CACNEA", 332, 32, R_COMUN, 0x3C49, 50, 85, 40, 35, TYPE_GRASS, TYPE_NONE, 2 },  // 331 grass
  { "CACTURNE", 0, 0, R_EVO, 0x3C49, 70, 115, 60, 55, TYPE_GRASS, TYPE_DARK, 2 },  // 332 grass/dark
  { "SWABLU", 334, 35, R_COMUN, 0x8C4D, 45, 40, 60, 50, TYPE_NORMAL, TYPE_FLYING, 0 },  // 333 normal/flying
  { "ALTARIA", 0, 0, R_EVO, 0x5A98, 75, 70, 90, 80, TYPE_DRAGON, TYPE_FLYING, 1 },  // 334 dragon/flying
  { "ZANGOOSE", 0, 0, R_RARO, 0x8C4D, 73, 115, 60, 90, TYPE_NORMAL, TYPE_NONE, 0 },  // 335 normal
  { "SEVIPER", 0, 0, R_RARO, 0x8A73, 73, 100, 60, 65, TYPE_POISON, TYPE_NONE, 0 },  // 336 poison
  { "LUNATONE", 0, 0, R_RARO, 0x9407, 90, 55, 65, 70, TYPE_ROCK, TYPE_PSYCHIC, 4 },  // 337 rock/psychic
  { "SOLROCK", 0, 0, R_RARO, 0x9407, 90, 95, 85, 70, TYPE_ROCK, TYPE_PSYCHIC, 4 },  // 338 rock/psychic
  { "BARBOACH", 340, 30, R_COMUN, 0x4C98, 50, 48, 43, 60, TYPE_WATER, TYPE_GROUND, 1 },  // 339 water/ground
  { "WHISCASH", 0, 0, R_EVO, 0x4C98, 110, 78, 73, 60, TYPE_WATER, TYPE_GROUND, 1 },  // 340 water/ground
  { "CORPHISH", 342, 30, R_COMUN, 0x4C98, 43, 80, 65, 35, TYPE_WATER, TYPE_NONE, 1 },  // 341 water
  { "CRAWDAUNT", 0, 0, R_EVO, 0x4C98, 63, 120, 85, 55, TYPE_WATER, TYPE_DARK, 1 },  // 342 water/dark
  { "BALTOY", 344, 36, R_COMUN, 0xB447, 40, 40, 55, 55, TYPE_GROUND, TYPE_PSYCHIC, 4 },  // 343 ground/psychic
  { "CLAYDOL", 0, 0, R_EVO, 0xB447, 60, 70, 105, 75, TYPE_GROUND, TYPE_PSYCHIC, 4 },  // 344 ground/psychic
  { "LILEEP", 346, 40, R_RARO, 0x9407, 66, 41, 77, 23, TYPE_ROCK, TYPE_GRASS, 4 },  // 345 rock/grass
  { "CRADILY", 0, 0, R_EVO, 0x9407, 86, 81, 97, 43, TYPE_ROCK, TYPE_GRASS, 4 },  // 346 rock/grass
  { "ANORITH", 348, 40, R_RARO, 0x9407, 45, 95, 50, 75, TYPE_ROCK, TYPE_BUG, 4 },  // 347 rock/bug
  { "ARMALDO", 0, 0, R_EVO, 0x9407, 75, 125, 100, 45, TYPE_ROCK, TYPE_BUG, 4 },  // 348 rock/bug
  { "FEEBAS", 350, 30, R_RARO, 0x4C98, 20, 15, 20, 80, TYPE_WATER, TYPE_NONE, 1 },  // 349 water
  { "MILOTIC", 0, 0, R_EVO, 0x4C98, 95, 60, 79, 81, TYPE_WATER, TYPE_NONE, 1 },  // 350 water
  { "CASTFORM", 0, 0, R_COMUN, 0x8C4D, 70, 70, 70, 70, TYPE_NORMAL, TYPE_NONE, 0 },  // 351 normal
  { "KECLEON", 0, 0, R_RARO, 0x8C4D, 60, 90, 70, 40, TYPE_NORMAL, TYPE_NONE, 0 },  // 352 normal
  { "SHUPPET", 354, 37, R_COMUN, 0x6AD3, 44, 75, 35, 45, TYPE_GHOST, TYPE_NONE, 0 },  // 353 ghost
  { "BANETTE", 0, 0, R_EVO, 0x6AD3, 64, 115, 65, 65, TYPE_GHOST, TYPE_NONE, 0 },  // 354 ghost
  { "DUSKULL", 356, 37, R_COMUN, 0x6AD3, 20, 40, 90, 25, TYPE_GHOST, TYPE_NONE, 0 },  // 355 ghost
  { "DUSCLOPS", 0, 0, R_EVO, 0x6AD3, 40, 70, 130, 25, TYPE_GHOST, TYPE_NONE, 0 },  // 356 ghost
  { "TROPIUS", 0, 0, R_RARO, 0x3C49, 99, 68, 83, 51, TYPE_GRASS, TYPE_FLYING, 2 },  // 357 grass/flying
  { "CHIMECHO", 0, 0, R_COMUN, 0xD28F, 75, 50, 80, 65, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 358 psychic
  { "ABSOL", 0, 0, R_RARO, 0x5A6E, 65, 130, 60, 75, TYPE_DARK, TYPE_NONE, 0 },  // 359 dark
  { "WYNAUT", 202, 15, R_COMUN, 0xD28F, 95, 23, 48, 23, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 360 psychic
  { "SNORUNT", 362, 42, R_RARO, 0x4DB8, 50, 50, 50, 50, TYPE_ICE, TYPE_NONE, 5 },  // 361 ice
  { "GLALIE", 0, 0, R_EVO, 0x4DB8, 80, 80, 80, 80, TYPE_ICE, TYPE_NONE, 5 },  // 362 ice
  { "SPHEAL", 364, 32, R_COMUN, 0x4DB8, 70, 40, 50, 25, TYPE_ICE, TYPE_WATER, 5 },  // 363 ice/water
  { "SEALEO", 365, 44, R_EVO, 0x4DB8, 90, 60, 70, 45, TYPE_ICE, TYPE_WATER, 5 },  // 364 ice/water
  { "WALREIN", 0, 0, R_EVO, 0x4DB8, 110, 80, 90, 65, TYPE_ICE, TYPE_WATER, 5 },  // 365 ice/water
  { "CLAMPERL", 367, 40, R_COMUN, 0x4C98, 35, 64, 85, 32, TYPE_WATER, TYPE_NONE, 1 },  // 366 water
  { "HUNTAIL", 0, 0, R_EVO, 0x4C98, 55, 104, 105, 52, TYPE_WATER, TYPE_NONE, 1 },  // 367 water
  { "GOREBYSS", 0, 0, R_EVO, 0x4C98, 55, 84, 105, 52, TYPE_WATER, TYPE_NONE, 1 },  // 368 water
  { "RELICANTH", 0, 0, R_RARO, 0x4C98, 100, 90, 130, 55, TYPE_WATER, TYPE_ROCK, 1 },  // 369 water/rock
  { "LUVDISC", 0, 0, R_RARO, 0x4C98, 43, 30, 55, 97, TYPE_WATER, TYPE_NONE, 1 },  // 370 water
  { "BAGON", 372, 30, R_RARO, 0x5A98, 45, 75, 60, 50, TYPE_DRAGON, TYPE_NONE, 1 },  // 371 dragon
  { "SHELGON", 373, 50, R_EVO, 0x5A98, 65, 95, 100, 50, TYPE_DRAGON, TYPE_NONE, 1 },  // 372 dragon
  { "SALAMENCE", 0, 0, R_EVO, 0x5A98, 95, 135, 80, 100, TYPE_DRAGON, TYPE_FLYING, 1 },  // 373 dragon/flying
  { "BELDUM", 375, 20, R_RARO, 0x7C73, 40, 55, 80, 30, TYPE_STEEL, TYPE_PSYCHIC, 4 },  // 374 steel/psychic
  { "METANG", 376, 45, R_EVO, 0x7C73, 60, 75, 100, 50, TYPE_STEEL, TYPE_PSYCHIC, 4 },  // 375 steel/psychic
  { "METAGROSS", 0, 0, R_EVO, 0x7C73, 80, 135, 130, 70, TYPE_STEEL, TYPE_PSYCHIC, 4 },  // 376 steel/psychic
  { "REGIROCK", 0, 0, R_LEGENDARIO, 0x9407, 80, 100, 200, 50, TYPE_ROCK, TYPE_NONE, 4 },  // 377 rock
  { "REGICE", 0, 0, R_LEGENDARIO, 0x4DB8, 80, 50, 100, 50, TYPE_ICE, TYPE_NONE, 5 },  // 378 ice
  { "REGISTEEL", 0, 0, R_LEGENDARIO, 0x7C73, 80, 75, 150, 50, TYPE_STEEL, TYPE_NONE, 4 },  // 379 steel
  { "LATIAS", 0, 0, R_LEGENDARIO, 0x5A98, 80, 80, 90, 110, TYPE_DRAGON, TYPE_PSYCHIC, 1 },  // 380 dragon/psychic
  { "LATIOS", 0, 0, R_LEGENDARIO, 0x5A98, 80, 90, 80, 110, TYPE_DRAGON, TYPE_PSYCHIC, 1 },  // 381 dragon/psychic
  { "KYOGRE", 0, 0, R_LEGENDARIO, 0x4C98, 100, 100, 90, 90, TYPE_WATER, TYPE_NONE, 1 },  // 382 water
  { "GROUDON", 0, 0, R_LEGENDARIO, 0xB447, 100, 150, 140, 90, TYPE_GROUND, TYPE_NONE, 4 },  // 383 ground
  { "RAYQUAZA", 0, 0, R_LEGENDARIO, 0x5A98, 105, 150, 90, 95, TYPE_DRAGON, TYPE_FLYING, 1 },  // 384 dragon/flying
  { "JIRACHI", 0, 0, R_LEGENDARIO, 0x7C73, 100, 100, 100, 100, TYPE_STEEL, TYPE_PSYCHIC, 4 },  // 385 steel/psychic
  { "DEOXYS", 0, 0, R_LEGENDARIO, 0xD28F, 50, 150, 50, 150, TYPE_PSYCHIC, TYPE_NONE, 0 },  // 386 psychic
};

// Evoluciones, incluidas ramas y condiciones especiales.
static const EvolutionRule EVOLUTION_RULES[] = {
  { 1, 2, 16, EVO_LEVEL },
  { 2, 3, 32, EVO_LEVEL },
  { 4, 5, 16, EVO_LEVEL },
  { 5, 6, 36, EVO_LEVEL },
  { 7, 8, 16, EVO_LEVEL },
  { 8, 9, 36, EVO_LEVEL },
  { 10, 11, 7, EVO_LEVEL },
  { 11, 12, 10, EVO_LEVEL },
  { 13, 14, 7, EVO_LEVEL },
  { 14, 15, 10, EVO_LEVEL },
  { 16, 17, 18, EVO_LEVEL },
  { 17, 18, 36, EVO_LEVEL },
  { 19, 20, 20, EVO_LEVEL },
  { 21, 22, 20, EVO_LEVEL },
  { 23, 24, 22, EVO_LEVEL },
  { 25, 26, 30, EVO_LEVEL },
  { 27, 28, 22, EVO_LEVEL },
  { 29, 30, 16, EVO_LEVEL },
  { 30, 31, 30, EVO_LEVEL },
  { 32, 33, 16, EVO_LEVEL },
  { 33, 34, 30, EVO_LEVEL },
  { 35, 36, 30, EVO_LEVEL },
  { 37, 38, 30, EVO_LEVEL },
  { 39, 40, 30, EVO_LEVEL },
  { 41, 42, 22, EVO_LEVEL },
  { 43, 44, 21, EVO_LEVEL },
  { 44, 45, 36, EVO_LEVEL },
  { 46, 47, 24, EVO_LEVEL },
  { 48, 49, 31, EVO_LEVEL },
  { 50, 51, 26, EVO_LEVEL },
  { 52, 53, 28, EVO_LEVEL },
  { 54, 55, 33, EVO_LEVEL },
  { 56, 57, 28, EVO_LEVEL },
  { 58, 59, 30, EVO_LEVEL },
  { 60, 61, 25, EVO_LEVEL },
  { 61, 62, 36, EVO_LEVEL },
  { 63, 64, 16, EVO_LEVEL },
  { 64, 65, 40, EVO_LEVEL },
  { 66, 67, 28, EVO_LEVEL },
  { 67, 68, 40, EVO_LEVEL },
  { 69, 70, 21, EVO_LEVEL },
  { 70, 71, 36, EVO_LEVEL },
  { 72, 73, 30, EVO_LEVEL },
  { 74, 75, 25, EVO_LEVEL },
  { 75, 76, 40, EVO_LEVEL },
  { 77, 78, 40, EVO_LEVEL },
  { 79, 80, 37, EVO_LEVEL },
  { 81, 82, 30, EVO_LEVEL },
  { 84, 85, 31, EVO_LEVEL },
  { 86, 87, 34, EVO_LEVEL },
  { 88, 89, 38, EVO_LEVEL },
  { 90, 91, 30, EVO_LEVEL },
  { 92, 93, 25, EVO_LEVEL },
  { 93, 94, 40, EVO_LEVEL },
  { 96, 97, 26, EVO_LEVEL },
  { 98, 99, 28, EVO_LEVEL },
  { 100, 101, 30, EVO_LEVEL },
  { 102, 103, 30, EVO_LEVEL },
  { 104, 105, 28, EVO_LEVEL },
  { 109, 110, 35, EVO_LEVEL },
  { 111, 112, 42, EVO_LEVEL },
  { 116, 117, 32, EVO_LEVEL },
  { 118, 119, 33, EVO_LEVEL },
  { 120, 121, 30, EVO_LEVEL },
  { 129, 130, 20, EVO_LEVEL },
  { 133, 134, 30, EVO_LEVEL },
  { 138, 139, 40, EVO_LEVEL },
  { 140, 141, 40, EVO_LEVEL },
  { 147, 148, 30, EVO_LEVEL },
  { 148, 149, 55, EVO_LEVEL },
  { 152, 153, 16, EVO_LEVEL },
  { 153, 154, 32, EVO_LEVEL },
  { 155, 156, 14, EVO_LEVEL },
  { 156, 157, 36, EVO_LEVEL },
  { 158, 159, 18, EVO_LEVEL },
  { 159, 160, 30, EVO_LEVEL },
  { 161, 162, 15, EVO_LEVEL },
  { 163, 164, 20, EVO_LEVEL },
  { 165, 166, 18, EVO_LEVEL },
  { 167, 168, 22, EVO_LEVEL },
  { 170, 171, 27, EVO_LEVEL },
  { 172, 25, 10, EVO_BOND },
  { 173, 35, 10, EVO_BOND },
  { 174, 39, 10, EVO_BOND },
  { 175, 176, 10, EVO_BOND },
  { 177, 178, 25, EVO_LEVEL },
  { 179, 180, 15, EVO_LEVEL },
  { 180, 181, 30, EVO_LEVEL },
  { 183, 184, 18, EVO_LEVEL },
  { 187, 188, 18, EVO_LEVEL },
  { 188, 189, 27, EVO_LEVEL },
  { 191, 192, 20, EVO_LEVEL },
  { 194, 195, 20, EVO_LEVEL },
  { 204, 205, 31, EVO_LEVEL },
  { 209, 210, 23, EVO_LEVEL },
  { 216, 217, 30, EVO_LEVEL },
  { 218, 219, 38, EVO_LEVEL },
  { 220, 221, 33, EVO_LEVEL },
  { 223, 224, 25, EVO_LEVEL },
  { 228, 229, 24, EVO_LEVEL },
  { 231, 232, 25, EVO_LEVEL },
  { 236, 106, 20, EVO_ATK_GT_DEF },
  { 236, 107, 20, EVO_DEF_GT_ATK },
  { 236, 237, 20, EVO_ATK_EQ_DEF },
  { 238, 124, 30, EVO_LEVEL },
  { 239, 125, 30, EVO_LEVEL },
  { 240, 126, 30, EVO_LEVEL },
  { 246, 247, 30, EVO_LEVEL },
  { 247, 248, 55, EVO_LEVEL },
  { 252, 253, 16, EVO_LEVEL },
  { 253, 254, 36, EVO_LEVEL },
  { 255, 256, 16, EVO_LEVEL },
  { 256, 257, 36, EVO_LEVEL },
  { 258, 259, 16, EVO_LEVEL },
  { 259, 260, 36, EVO_LEVEL },
  { 261, 262, 18, EVO_LEVEL },
  { 263, 264, 20, EVO_LEVEL },
  { 265, 266, 7, EVO_LEVEL },
  { 266, 267, 10, EVO_LEVEL },
  { 268, 269, 10, EVO_LEVEL },
  { 270, 271, 14, EVO_LEVEL },
  { 271, 272, 30, EVO_LEVEL },
  { 273, 274, 14, EVO_LEVEL },
  { 274, 275, 30, EVO_LEVEL },
  { 276, 277, 22, EVO_LEVEL },
  { 278, 279, 25, EVO_LEVEL },
  { 280, 281, 20, EVO_LEVEL },
  { 281, 282, 30, EVO_LEVEL },
  { 283, 284, 22, EVO_LEVEL },
  { 285, 286, 23, EVO_LEVEL },
  { 287, 288, 18, EVO_LEVEL },
  { 288, 289, 36, EVO_LEVEL },
  { 290, 291, 20, EVO_LEVEL },
  { 293, 294, 20, EVO_LEVEL },
  { 294, 295, 40, EVO_LEVEL },
  { 296, 297, 24, EVO_LEVEL },
  { 298, 183, 10, EVO_BOND },
  { 300, 301, 30, EVO_LEVEL },
  { 304, 305, 32, EVO_LEVEL },
  { 305, 306, 42, EVO_LEVEL },
  { 307, 308, 37, EVO_LEVEL },
  { 309, 310, 26, EVO_LEVEL },
  { 316, 317, 26, EVO_LEVEL },
  { 318, 319, 30, EVO_LEVEL },
  { 320, 321, 40, EVO_LEVEL },
  { 322, 323, 33, EVO_LEVEL },
  { 325, 326, 32, EVO_LEVEL },
  { 328, 329, 35, EVO_LEVEL },
  { 329, 330, 45, EVO_LEVEL },
  { 331, 332, 32, EVO_LEVEL },
  { 333, 334, 35, EVO_LEVEL },
  { 339, 340, 30, EVO_LEVEL },
  { 341, 342, 30, EVO_LEVEL },
  { 343, 344, 36, EVO_LEVEL },
  { 345, 346, 40, EVO_LEVEL },
  { 347, 348, 40, EVO_LEVEL },
  { 349, 350, 30, EVO_BOND },
  { 353, 354, 37, EVO_LEVEL },
  { 355, 356, 37, EVO_LEVEL },
  { 360, 202, 15, EVO_LEVEL },
  { 361, 362, 42, EVO_LEVEL },
  { 363, 364, 32, EVO_LEVEL },
  { 364, 365, 44, EVO_LEVEL },
  { 366, 367, 40, EVO_LEVEL },
  { 371, 372, 30, EVO_LEVEL },
  { 372, 373, 50, EVO_LEVEL },
  { 374, 375, 20, EVO_LEVEL },
  { 375, 376, 45, EVO_LEVEL },
  { 42, 169, 30, EVO_BOND },
  { 44, 182, 36, EVO_LEVEL },
  { 61, 186, 36, EVO_LEVEL },
  { 79, 199, 37, EVO_LEVEL },
  { 95, 208, 30, EVO_LEVEL },
  { 113, 242, 30, EVO_BOND },
  { 117, 230, 42, EVO_LEVEL },
  { 123, 212, 30, EVO_LEVEL },
  { 133, 135, 30, EVO_LEVEL },
  { 133, 136, 30, EVO_LEVEL },
  { 133, 196, 30, EVO_DAY_BOND },
  { 133, 197, 30, EVO_NIGHT_BOND },
  { 137, 233, 30, EVO_LEVEL },
  { 265, 268, 7, EVO_LEVEL },
  { 290, 292, 20, EVO_LEVEL },
  { 366, 368, 40, EVO_LEVEL },
};
#define EVOLUTION_RULE_COUNT 184

// nombres localizados en el orden de Lang: ES, EN, FR, DE, IT, PT
static const char *const DEX_NAMES[DEX_LANG_COUNT][DEX_COUNT + 1] = {
  // ES
  { "?", "BULBASAUR", "IVYSAUR", "VENUSAUR", "CHARMANDER", "CHARMELEON", "CHARIZARD", "SQUIRTLE", "WARTORTLE", "BLASTOISE", "CATERPIE", "METAPOD", "BUTTERFREE", "WEEDLE", "KAKUNA", "BEEDRILL", "PIDGEY", "PIDGEOTTO", "PIDGEOT", "RATTATA", "RATICATE", "SPEAROW", "FEAROW", "EKANS", "ARBOK", "PIKACHU", "RAICHU", "SANDSHREW", "SANDSLASH", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "CLEFAIRY", "CLEFABLE", "VULPIX", "NINETALES", "JIGGLYPUFF", "WIGGLYTUFF", "ZUBAT", "GOLBAT", "ODDISH", "GLOOM", "VILEPLUME", "PARAS", "PARASECT", "VENONAT", "VENOMOTH", "DIGLETT", "DUGTRIO", "MEOWTH", "PERSIAN", "PSYDUCK", "GOLDUCK", "MANKEY", "PRIMEAPE", "GROWLITHE", "ARCANINE", "POLIWAG", "POLIWHIRL", "POLIWRATH", "ABRA", "KADABRA", "ALAKAZAM", "MACHOP", "MACHOKE", "MACHAMP", "BELLSPROUT", "WEEPINBELL", "VICTREEBEL", "TENTACOOL", "TENTACRUEL", "GEODUDE", "GRAVELER", "GOLEM", "PONYTA", "RAPIDASH", "SLOWPOKE", "SLOWBRO", "MAGNEMITE", "MAGNETON", "FARFETCHD", "DODUO", "DODRIO", "SEEL", "DEWGONG", "GRIMER", "MUK", "SHELLDER", "CLOYSTER", "GASTLY", "HAUNTER", "GENGAR", "ONIX", "DROWZEE", "HYPNO", "KRABBY", "KINGLER", "VOLTORB", "ELECTRODE", "EXEGGCUTE", "EXEGGUTOR", "CUBONE", "MAROWAK", "HITMONLEE", "HITMONCHAN", "LICKITUNG", "KOFFING", "WEEZING", "RHYHORN", "RHYDON", "CHANSEY", "TANGELA", "KANGASKHAN", "HORSEA", "SEADRA", "GOLDEEN", "SEAKING", "STARYU", "STARMIE", "MR. MIME", "SCYTHER", "JYNX", "ELECTABUZZ", "MAGMAR", "PINSIR", "TAUROS", "MAGIKARP", "GYARADOS", "LAPRAS", "DITTO", "EEVEE", "VAPOREON", "JOLTEON", "FLAREON", "PORYGON", "OMANYTE", "OMASTAR", "KABUTO", "KABUTOPS", "AERODACTYL", "SNORLAX", "ARTICUNO", "ZAPDOS", "MOLTRES", "DRATINI", "DRAGONAIR", "DRAGONITE", "MEWTWO", "MEW", "CHIKORITA", "BAYLEEF", "MEGANIUM", "CYNDAQUIL", "QUILAVA", "TYPHLOSION", "TOTODILE", "CROCONAW", "FERALIGATR", "SENTRET", "FURRET", "HOOTHOOT", "NOCTOWL", "LEDYBA", "LEDIAN", "SPINARAK", "ARIADOS", "CROBAT", "CHINCHOU", "LANTURN", "PICHU", "CLEFFA", "IGGLYBUFF", "TOGEPI", "TOGETIC", "NATU", "XATU", "MAREEP", "FLAAFFY", "AMPHAROS", "BELLOSSOM", "MARILL", "AZUMARILL", "SUDOWOODO", "POLITOED", "HOPPIP", "SKIPLOOM", "JUMPLUFF", "AIPOM", "SUNKERN", "SUNFLORA", "YANMA", "WOOPER", "QUAGSIRE", "ESPEON", "UMBREON", "MURKROW", "SLOWKING", "MISDREAVUS", "UNOWN", "WOBBUFFET", "GIRAFARIG", "PINECO", "FORRETRESS", "DUNSPARCE", "GLIGAR", "STEELIX", "SNUBBULL", "GRANBULL", "QWILFISH", "SCIZOR", "SHUCKLE", "HERACROSS", "SNEASEL", "TEDDIURSA", "URSARING", "SLUGMA", "MAGCARGO", "SWINUB", "PILOSWINE", "CORSOLA", "REMORAID", "OCTILLERY", "DELIBIRD", "MANTINE", "SKARMORY", "HOUNDOUR", "HOUNDOOM", "KINGDRA", "PHANPY", "DONPHAN", "PORYGON2", "STANTLER", "SMEARGLE", "TYROGUE", "HITMONTOP", "SMOOCHUM", "ELEKID", "MAGBY", "MILTANK", "BLISSEY", "RAIKOU", "ENTEI", "SUICUNE", "LARVITAR", "PUPITAR", "TYRANITAR", "LUGIA", "HO_OH", "CELEBI", "TREECKO", "GROVYLE", "SCEPTILE", "TORCHIC", "COMBUSKEN", "BLAZIKEN", "MUDKIP", "MARSHTOMP", "SWAMPERT", "POOCHYENA", "MIGHTYENA", "ZIGZAGOON", "LINOONE", "WURMPLE", "SILCOON", "BEAUTIFLY", "CASCOON", "DUSTOX", "LOTAD", "LOMBRE", "LUDICOLO", "SEEDOT", "NUZLEAF", "SHIFTRY", "TAILLOW", "SWELLOW", "WINGULL", "PELIPPER", "RALTS", "KIRLIA", "GARDEVOIR", "SURSKIT", "MASQUERAIN", "SHROOMISH", "BRELOOM", "SLAKOTH", "VIGOROTH", "SLAKING", "NINCADA", "NINJASK", "SHEDINJA", "WHISMUR", "LOUDRED", "EXPLOUD", "MAKUHITA", "HARIYAMA", "AZURILL", "NOSEPASS", "SKITTY", "DELCATTY", "SABLEYE", "MAWILE", "ARON", "LAIRON", "AGGRON", "MEDITITE", "MEDICHAM", "ELECTRIKE", "MANECTRIC", "PLUSLE", "MINUN", "VOLBEAT", "ILLUMISE", "ROSELIA", "GULPIN", "SWALOT", "CARVANHA", "SHARPEDO", "WAILMER", "WAILORD", "NUMEL", "CAMERUPT", "TORKOAL", "SPOINK", "GRUMPIG", "SPINDA", "TRAPINCH", "VIBRAVA", "FLYGON", "CACNEA", "CACTURNE", "SWABLU", "ALTARIA", "ZANGOOSE", "SEVIPER", "LUNATONE", "SOLROCK", "BARBOACH", "WHISCASH", "CORPHISH", "CRAWDAUNT", "BALTOY", "CLAYDOL", "LILEEP", "CRADILY", "ANORITH", "ARMALDO", "FEEBAS", "MILOTIC", "CASTFORM", "KECLEON", "SHUPPET", "BANETTE", "DUSKULL", "DUSCLOPS", "TROPIUS", "CHIMECHO", "ABSOL", "WYNAUT", "SNORUNT", "GLALIE", "SPHEAL", "SEALEO", "WALREIN", "CLAMPERL", "HUNTAIL", "GOREBYSS", "RELICANTH", "LUVDISC", "BAGON", "SHELGON", "SALAMENCE", "BELDUM", "METANG", "METAGROSS", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
  // EN
  { "?", "BULBASAUR", "IVYSAUR", "VENUSAUR", "CHARMANDER", "CHARMELEON", "CHARIZARD", "SQUIRTLE", "WARTORTLE", "BLASTOISE", "CATERPIE", "METAPOD", "BUTTERFREE", "WEEDLE", "KAKUNA", "BEEDRILL", "PIDGEY", "PIDGEOTTO", "PIDGEOT", "RATTATA", "RATICATE", "SPEAROW", "FEAROW", "EKANS", "ARBOK", "PIKACHU", "RAICHU", "SANDSHREW", "SANDSLASH", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "CLEFAIRY", "CLEFABLE", "VULPIX", "NINETALES", "JIGGLYPUFF", "WIGGLYTUFF", "ZUBAT", "GOLBAT", "ODDISH", "GLOOM", "VILEPLUME", "PARAS", "PARASECT", "VENONAT", "VENOMOTH", "DIGLETT", "DUGTRIO", "MEOWTH", "PERSIAN", "PSYDUCK", "GOLDUCK", "MANKEY", "PRIMEAPE", "GROWLITHE", "ARCANINE", "POLIWAG", "POLIWHIRL", "POLIWRATH", "ABRA", "KADABRA", "ALAKAZAM", "MACHOP", "MACHOKE", "MACHAMP", "BELLSPROUT", "WEEPINBELL", "VICTREEBEL", "TENTACOOL", "TENTACRUEL", "GEODUDE", "GRAVELER", "GOLEM", "PONYTA", "RAPIDASH", "SLOWPOKE", "SLOWBRO", "MAGNEMITE", "MAGNETON", "FARFETCHD", "DODUO", "DODRIO", "SEEL", "DEWGONG", "GRIMER", "MUK", "SHELLDER", "CLOYSTER", "GASTLY", "HAUNTER", "GENGAR", "ONIX", "DROWZEE", "HYPNO", "KRABBY", "KINGLER", "VOLTORB", "ELECTRODE", "EXEGGCUTE", "EXEGGUTOR", "CUBONE", "MAROWAK", "HITMONLEE", "HITMONCHAN", "LICKITUNG", "KOFFING", "WEEZING", "RHYHORN", "RHYDON", "CHANSEY", "TANGELA", "KANGASKHAN", "HORSEA", "SEADRA", "GOLDEEN", "SEAKING", "STARYU", "STARMIE", "MR. MIME", "SCYTHER", "JYNX", "ELECTABUZZ", "MAGMAR", "PINSIR", "TAUROS", "MAGIKARP", "GYARADOS", "LAPRAS", "DITTO", "EEVEE", "VAPOREON", "JOLTEON", "FLAREON", "PORYGON", "OMANYTE", "OMASTAR", "KABUTO", "KABUTOPS", "AERODACTYL", "SNORLAX", "ARTICUNO", "ZAPDOS", "MOLTRES", "DRATINI", "DRAGONAIR", "DRAGONITE", "MEWTWO", "MEW", "CHIKORITA", "BAYLEEF", "MEGANIUM", "CYNDAQUIL", "QUILAVA", "TYPHLOSION", "TOTODILE", "CROCONAW", "FERALIGATR", "SENTRET", "FURRET", "HOOTHOOT", "NOCTOWL", "LEDYBA", "LEDIAN", "SPINARAK", "ARIADOS", "CROBAT", "CHINCHOU", "LANTURN", "PICHU", "CLEFFA", "IGGLYBUFF", "TOGEPI", "TOGETIC", "NATU", "XATU", "MAREEP", "FLAAFFY", "AMPHAROS", "BELLOSSOM", "MARILL", "AZUMARILL", "SUDOWOODO", "POLITOED", "HOPPIP", "SKIPLOOM", "JUMPLUFF", "AIPOM", "SUNKERN", "SUNFLORA", "YANMA", "WOOPER", "QUAGSIRE", "ESPEON", "UMBREON", "MURKROW", "SLOWKING", "MISDREAVUS", "UNOWN", "WOBBUFFET", "GIRAFARIG", "PINECO", "FORRETRESS", "DUNSPARCE", "GLIGAR", "STEELIX", "SNUBBULL", "GRANBULL", "QWILFISH", "SCIZOR", "SHUCKLE", "HERACROSS", "SNEASEL", "TEDDIURSA", "URSARING", "SLUGMA", "MAGCARGO", "SWINUB", "PILOSWINE", "CORSOLA", "REMORAID", "OCTILLERY", "DELIBIRD", "MANTINE", "SKARMORY", "HOUNDOUR", "HOUNDOOM", "KINGDRA", "PHANPY", "DONPHAN", "PORYGON2", "STANTLER", "SMEARGLE", "TYROGUE", "HITMONTOP", "SMOOCHUM", "ELEKID", "MAGBY", "MILTANK", "BLISSEY", "RAIKOU", "ENTEI", "SUICUNE", "LARVITAR", "PUPITAR", "TYRANITAR", "LUGIA", "HO_OH", "CELEBI", "TREECKO", "GROVYLE", "SCEPTILE", "TORCHIC", "COMBUSKEN", "BLAZIKEN", "MUDKIP", "MARSHTOMP", "SWAMPERT", "POOCHYENA", "MIGHTYENA", "ZIGZAGOON", "LINOONE", "WURMPLE", "SILCOON", "BEAUTIFLY", "CASCOON", "DUSTOX", "LOTAD", "LOMBRE", "LUDICOLO", "SEEDOT", "NUZLEAF", "SHIFTRY", "TAILLOW", "SWELLOW", "WINGULL", "PELIPPER", "RALTS", "KIRLIA", "GARDEVOIR", "SURSKIT", "MASQUERAIN", "SHROOMISH", "BRELOOM", "SLAKOTH", "VIGOROTH", "SLAKING", "NINCADA", "NINJASK", "SHEDINJA", "WHISMUR", "LOUDRED", "EXPLOUD", "MAKUHITA", "HARIYAMA", "AZURILL", "NOSEPASS", "SKITTY", "DELCATTY", "SABLEYE", "MAWILE", "ARON", "LAIRON", "AGGRON", "MEDITITE", "MEDICHAM", "ELECTRIKE", "MANECTRIC", "PLUSLE", "MINUN", "VOLBEAT", "ILLUMISE", "ROSELIA", "GULPIN", "SWALOT", "CARVANHA", "SHARPEDO", "WAILMER", "WAILORD", "NUMEL", "CAMERUPT", "TORKOAL", "SPOINK", "GRUMPIG", "SPINDA", "TRAPINCH", "VIBRAVA", "FLYGON", "CACNEA", "CACTURNE", "SWABLU", "ALTARIA", "ZANGOOSE", "SEVIPER", "LUNATONE", "SOLROCK", "BARBOACH", "WHISCASH", "CORPHISH", "CRAWDAUNT", "BALTOY", "CLAYDOL", "LILEEP", "CRADILY", "ANORITH", "ARMALDO", "FEEBAS", "MILOTIC", "CASTFORM", "KECLEON", "SHUPPET", "BANETTE", "DUSKULL", "DUSCLOPS", "TROPIUS", "CHIMECHO", "ABSOL", "WYNAUT", "SNORUNT", "GLALIE", "SPHEAL", "SEALEO", "WALREIN", "CLAMPERL", "HUNTAIL", "GOREBYSS", "RELICANTH", "LUVDISC", "BAGON", "SHELGON", "SALAMENCE", "BELDUM", "METANG", "METAGROSS", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
  // FR
  { "?", "BULBIZARRE", "HERBIZARRE", "FLORIZARRE", "SALAMECHE", "REPTINCEL", "DRACAUFEU", "CARAPUCE", "CARABAFFE", "TORTANK", "CHENIPAN", "CHRYSACIER", "PAPILUSION", "ASPICOT", "COCONFORT", "DARDARGNAN", "ROUCOOL", "ROUCOUPS", "ROUCARNAGE", "RATTATA", "RATTATAC", "PIAFABEC", "RAPASDEPIC", "ABO", "ARBOK", "PIKACHU", "RAICHU", "SABELETTE", "SABLAIREAU", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "MELOFEE", "MELODELFE", "GOUPIX", "FEUNARD", "RONDOUDOU", "GRODOUDOU", "NOSFERAPTI", "NOSFERALTO", "MYSTHERBE", "ORTIDE", "RAFFLESIA", "PARAS", "PARASECT", "MIMITOSS", "AEROMITE", "TAUPIQUEUR", "TRIOPIKEUR", "MIAOUSS", "PERSIAN", "PSYKOKWAK", "AKWAKWAK", "FEROSINGE", "COLOSSINGE", "CANINOS", "ARCANIN", "PTITARD", "TETARTE", "TARTARD", "ABRA", "KADABRA", "ALAKAZAM", "MACHOC", "MACHOPEUR", "MACKOGNEUR", "CHETIFLOR", "BOUSTIFLOR", "EMPIFLOR", "TENTACOOL", "TENTACRUEL", "RACAILLOU", "GRAVALANCH", "GROLEM", "PONYTA", "GALOPA", "RAMOLOSS", "FLAGADOSS", "MAGNETI", "MAGNETON", "CANARTICHO", "DODUO", "DODRIO", "OTARIA", "LAMANTINE", "TADMORV", "GROTADMORV", "KOKIYAS", "CRUSTABRI", "FANTOMINUS", "SPECTRUM", "ECTOPLASMA", "ONIX", "SOPORIFIK", "HYPNOMADE", "KRABBY", "KRABBOSS", "VOLTORBE", "ELECTRODE", "NOEUNOEUF", "NOADKOKO", "OSSELAIT", "OSSATUEUR", "KICKLEE", "TYGNON", "EXCELANGUE", "SMOGO", "SMOGOGO", "RHINOCORNE", "RHINOFEROS", "LEVEINARD", "SAQUEDENEU", "KANGOUREX", "HYPOTREMPE", "HYPOCEAN", "POISSIRENE", "POISSOROY", "STARI", "STAROSS", "M. MIME", "INSECATEUR", "LIPPOUTOU", "ELEKTEK", "MAGMAR", "SCARABRUTE", "TAUROS", "MAGICARPE", "LEVIATOR", "LOKHLASS", "METAMORPH", "EVOLI", "AQUALI", "VOLTALI", "PYROLI", "PORYGON", "AMONITA", "AMONISTAR", "KABUTO", "KABUTOPS", "PTERA", "RONFLEX", "ARTIKODIN", "ELECTHOR", "SULFURA", "MINIDRACO", "DRACO", "DRACOLOSSE", "MEWTWO", "MEW", "GERMIGNON", "MACRONIUM", "MEGANIUM", "HERICENDRE", "FEURISSON", "TYPHLOSION", "KAIMINUS", "CROCRODIL", "ALIGATUEUR", "FOUINET", "FOUINAR", "HOOTHOOT", "NOARFANG", "COXY", "COXICLAQUE", "MIMIGAL", "MIGALOS", "NOSTENFER", "LOUPIO", "LANTURN", "PICHU", "MELOFEE", "TOUDOUDOU", "TOGEPI", "TOGETIC", "NATU", "XATU", "WATTWAP", "LAINERGIE", "PHARAMP", "JOLIFLOR", "MARILL", "AZUMARILL", "SIMULARBRE", "TARPAUD", "GRANIVOL", "FLORAVOL", "COTOVOL", "CAPUMAIN", "TOURNEGRIN", "HELIATRONC", "YANMA", "AXOLOTO", "MARAISTE", "MENTALI", "NOCTALI", "CORNEBRE", "ROIGADA", "FEUFOREVE", "ZARBI", "QULBUTOKE", "GIRAFARIG", "POMDEPIK", "FORETRESS", "INSOLOURDO", "SCORPLANE", "STEELIX", "SNUBBULL", "GRANBULL", "QWILFISH", "CIZAYOX", "CARATROC", "SCARHINO", "FARFURET", "TEDDIURSA", "URSARING", "LIMAGMA", "VOLCAROPOD", "MARCACRIN", "COCHIGNON", "CORAYON", "REMORAID", "OCTILLERY", "CADOIZO", "DEMANTA", "AIRMURE", "MALOSSE", "DEMOLOSSE", "HYPOROI", "PHANPY", "DONPHAN", "PORYGON2", "CERFROUSSE", "QUEULORIOR", "DEBUGANT", "KAPOERA", "LIPPOUTI", "ELEKID", "MAGBY", "ECREMEUH", "LEUPHORIE", "RAIKOU", "ENTEI", "SUICUNE", "EMBRYLEX", "YMPHECT", "TYRANOCIF", "LUGIA", "HO_OH", "CELEBI", "ARCKO", "MASSKO", "JUNGKO", "POUSSIFEU", "GALIFEU", "BRASEGALI", "GOBOU", "FLOBIO", "LAGGRON", "MEDHYENA", "GRAHYENA", "ZIGZATON", "LINEON", "CHENIPOTTE", "ARMULYS", "CHARMILLON", "BLINDALYS", "PAPINOX", "NENUPIOT", "LOMBRE", "LUDICOLO", "GRAINIPIOT", "PIFEUIL", "TENGALICE", "NIRONDELLE", "HELEDELLE", "GOELISE", "BEKIPAN", "TARSAL", "KIRLIA", "GARDEVOIR", "ARAKDO", "MASKADRA", "BALIGNON", "CHAPIGNON", "PARECOOL", "VIGOROTH", "MONAFLEMIT", "NINGALE", "NINJASK", "MUNJA", "CHUCHMUR", "RAMBOUM", "BROUHABAM", "MAKUHITA", "HARIYAMA", "AZURILL", "TARINOR", "SKITTY", "DELCATTY", "TENEFIX", "MYSDIBULE", "GALEKID", "GALEGON", "GALEKING", "MEDITIKKA", "CHARMINA", "DYNAVOLT", "ELECSPRINT", "POSIPI", "NEGAPI", "MUCIOLE", "LUMIVOLE", "ROSELIA", "GLOUPTI", "AVALTOUT", "CARVANHA", "SHARPEDO", "WAILMER", "WAILORD", "CHAMALLOT", "CAMERUPT", "CHARTOR", "SPOINK", "GRORET", "SPINDA", "KRAKNOIX", "VIBRANINF", "LIBEGON", "CACNEA", "CACTURNE", "TYLTON", "ALTARIA", "MANGRIFF", "SEVIPER", "SELEROC", "SOLAROC", "BARLOCHE", "BARBICHA", "ECRAPINCE", "COLHOMARD", "BALBUTO", "KAORINE", "LILIA", "VACILYS", "ANORITH", "ARMALDO", "BARPAU", "MILOBELLUS", "MORPHEO", "KECLEON", "POLICHOMBR", "BRANETTE", "SKELENOX", "TERACLOPE", "TROPIUS", "EOKO", "ABSOL", "OKEOKE", "STALGAMIN", "ONIGLALI", "OBALIE", "PHOGLEUR", "KAIMORSE", "COQUIPERL", "SERPANG", "ROSABYSS", "RELICANTH", "LOVDISC", "DRABY", "DRACKHAUS", "DRATTAK", "TERHAL", "METANG", "METALOSSE", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
  // DE
  { "?", "BISASAM", "BISAKNOSP", "BISAFLOR", "GLUMANDA", "GLUTEXO", "GLURAK", "SCHIGGY", "SCHILLOK", "TURTOK", "RAUPY", "SAFCON", "SMETTBO", "HORNLIU", "KOKUNA", "BIBOR", "TAUBSI", "TAUBOGA", "TAUBOSS", "RATTFRATZ", "RATTIKARL", "HABITAK", "IBITAK", "RETTAN", "ARBOK", "PIKACHU", "RAICHU", "SANDAN", "SANDAMER", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "PIEPI", "PIXI", "VULPIX", "VULNONA", "PUMMELUFF", "KNUDDELUFF", "ZUBAT", "GOLBAT", "MYRAPLA", "DUFLOR", "GIFLOR", "PARAS", "PARASEK", "BLUZUK", "OMOT", "DIGDA", "DIGDRI", "MAUZI", "SNOBILIKAT", "ENTON", "ENTORON", "MENKI", "RASAFF", "FUKANO", "ARKANI", "QUAPSEL", "QUAPUTZI", "QUAPPO", "ABRA", "KADABRA", "SIMSALA", "MACHOLLO", "MASCHOCK", "MACHOMEI", "KNOFENSA", "ULTRIGARIA", "SARZENIA", "TENTACHA", "TENTOXA", "KLEINSTEIN", "GEOROK", "GEOWAZ", "PONITA", "GALLOPA", "FLEGMON", "LAHMUS", "MAGNETILO", "MAGNETON", "PORENTA", "DODU", "DODRI", "JUROB", "JUGONG", "SLEIMA", "SLEIMOK", "MUSCHAS", "AUSTOS", "NEBULAK", "ALPOLLO", "GENGAR", "ONIX", "TRAUMATO", "HYPNO", "KRABBY", "KINGLER", "VOLTOBAL", "LEKTROBAL", "OWEI", "KOKOWEI", "TRAGOSSO", "KNOGGA", "KICKLEE", "NOCKCHAN", "SCHLURP", "SMOGON", "SMOGMOG", "RIHORN", "RIZEROS", "CHANEIRA", "TANGELA", "KANGAMA", "SEEPER", "SEEMON", "GOLDINI", "GOLKING", "STERNDU", "STARMIE", "PANTIMOS", "SICHLOR", "ROSSANA", "ELEKTEK", "MAGMAR", "PINSIR", "TAUROS", "KARPADOR", "GARADOS", "LAPRAS", "DITTO", "EVOLI", "AQUANA", "BLITZA", "FLAMARA", "PORYGON", "AMONITAS", "AMOROSO", "KABUTO", "KABUTOPS", "AERODACTYL", "RELAXO", "ARKTOS", "ZAPDOS", "LAVADOS", "DRATINI", "DRAGONIR", "DRAGORAN", "MEWTU", "MEW", "ENDIVIE", "LORBLATT", "MEGANIE", "FEURIGEL", "IGELAVAR", "TORNUPTO", "KARNIMANI", "TYRACROC", "IMPERGATOR", "WIESOR", "WIESENIOR", "HOOTHOOT", "NOCTUH", "LEDYBA", "LEDIAN", "WEBARAK", "ARIADOS", "KROBAT", "LAMPI", "LANTURN", "PICHU", "PII", "PUMMELUFF", "TOGEPI", "TOGETIC", "NATU", "XATU", "WATTZAPF", "WAATY", "AMPHAROS", "BLUBELLA", "MARILL", "AZUMARILL", "MOGELBAUM", "QUAXO", "HOPPSPROSS", "HUBELUPF", "PAPUNGHA", "GRIFFEL", "SONNKERN", "SONNFLORA", "YANMA", "QUAPSEL", "MORLORD", "PSIANA", "NACHTARA", "KRAMURX", "LASCHOKING", "TRAUNFUGIL", "ICOGNITO", "WOINGENAU", "GIRAFARIG", "TANNZA", "FORSTELLA", "DUMMISEL", "SKORGLA", "STAHLIX", "SNUBBULL", "GRANBULL", "QWILFISH", "SCHEROX", "POTTROTT", "SKARABORN", "SNIEBEL", "TEDDIURSA", "URSARING", "SCHNECKMAG", "MAGCARGO", "QUIEKEL", "KEIFEL", "CORASONN", "REMORAID", "OCTILLERY", "BOTOGEL", "MANTAX", "PANZAERON", "HUNDUSTER", "HUNDEMON", "SEEDRAKING", "PHANPY", "DONPHAN", "PORYGON2", "DAMHIRPLEX", "FARBEAGLE", "RABAUZ", "KAPOERA", "KUSSILLA", "ELEKID", "MAGBY", "MILTANK", "HEITEIRA", "RAIKOU", "ENTEI", "SUICUNE", "LARVITAR", "PUPITAR", "DESPOTAR", "LUGIA", "HO_OH", "CELEBI", "GECKARBOR", "REPTAIN", "GEWALDRO", "FLEMMLI", "JUNGGLUT", "LOHGOCK", "HYDROPI", "MOORABBEL", "SUMPEX", "FIFFYEN", "MAGNAYEN", "ZIGZACHS", "GERADAKS", "WAUMPEL", "SCHALOKO", "PAPINELLA", "PANEKON", "PUDOX", "LOTURZEL", "LOMBRERO", "KAPPALORES", "SAMURZEL", "BLANAS", "TENGULIST", "SCHWALBINI", "SCHWALBOSS", "WINGULL", "PELIPPER", "TRASLA", "KIRLIA", "GUARDEVOIR", "GEHWEIHER", "MASKEREGEN", "KNILZ", "KAPILZ", "BUMMELZ", "MUNTIER", "LETARKING", "NINCADA", "NINJASK", "NINJATOM", "FLURMEL", "KRAKEELO", "KRAWUMMS", "MAKUHITA", "HARIYAMA", "AZURILL", "NASGNET", "ENECO", "ENEKORO", "ZOBIRIS", "FLUNKIFER", "STOLLUNIOR", "STOLLRAK", "STOLLOSS", "MEDITIE", "MEDITALIS", "FRIZELBLIZ", "VOLTENSO", "PLUSLE", "MINUN", "VOLBEAT", "ILLUMISE", "ROSELIA", "SCHLUPPUCK", "SCHLUKWECH", "KANIVANHA", "TOHAIDO", "WAILMER", "WAILORD", "CAMAUB", "CAMERUPT", "QURTEL", "SPOINK", "GROINK", "PANDIR", "KNACKLION", "VIBRAVA", "LIBELLDRA", "TUSKA", "NOKTUSKA", "WABLU", "ALTARIA", "SENGO", "VIPITIS", "LUNASTEIN", "SONNFEL", "SCHMERBE", "WELSAR", "KREBSCORPS", "KREBUTACK", "PUPPANCE", "LEPUMENTAS", "LILIEP", "WIELIE", "ANORITH", "ARMALDO", "BARSCHWA", "MILOTIC", "FORMEO", "KECLEON", "SHUPPET", "BANETTE", "ZWIRRLICHT", "ZWIRRKLOP", "TROPIUS", "PALIMPALIM", "ABSOL", "ISSO", "SCHNEPPKE", "FIRNONTOR", "SEEMOPS", "SEEJONG", "WALRAISA", "PERLU", "AALABYSS", "SAGANABYSS", "RELICANTH", "LIEBISKUS", "KINDWURM", "DRASCHEL", "BRUTALANDA", "TANHEL", "METANG", "METAGROSS", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
  // IT
  { "?", "BULBASAUR", "IVYSAUR", "VENUSAUR", "CHARMANDER", "CHARMELEON", "CHARIZARD", "SQUIRTLE", "WARTORTLE", "BLASTOISE", "CATERPIE", "METAPOD", "BUTTERFREE", "WEEDLE", "KAKUNA", "BEEDRILL", "PIDGEY", "PIDGEOTTO", "PIDGEOT", "RATTATA", "RATICATE", "SPEAROW", "FEAROW", "EKANS", "ARBOK", "PIKACHU", "RAICHU", "SANDSHREW", "SANDSLASH", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "CLEFAIRY", "CLEFABLE", "VULPIX", "NINETALES", "JIGGLYPUFF", "WIGGLYTUFF", "ZUBAT", "GOLBAT", "ODDISH", "GLOOM", "VILEPLUME", "PARAS", "PARASECT", "VENONAT", "VENOMOTH", "DIGLETT", "DUGTRIO", "MEOWTH", "PERSIAN", "PSYDUCK", "GOLDUCK", "MANKEY", "PRIMEAPE", "GROWLITHE", "ARCANINE", "POLIWAG", "POLIWHIRL", "POLIWRATH", "ABRA", "KADABRA", "ALAKAZAM", "MACHOP", "MACHOKE", "MACHAMP", "BELLSPROUT", "WEEPINBELL", "VICTREEBEL", "TENTACOOL", "TENTACRUEL", "GEODUDE", "GRAVELER", "GOLEM", "PONYTA", "RAPIDASH", "SLOWPOKE", "SLOWBRO", "MAGNEMITE", "MAGNETON", "FARFETCHD", "DODUO", "DODRIO", "SEEL", "DEWGONG", "GRIMER", "MUK", "SHELLDER", "CLOYSTER", "GASTLY", "HAUNTER", "GENGAR", "ONIX", "DROWZEE", "HYPNO", "KRABBY", "KINGLER", "VOLTORB", "ELECTRODE", "EXEGGCUTE", "EXEGGUTOR", "CUBONE", "MAROWAK", "HITMONLEE", "HITMONCHAN", "LICKITUNG", "KOFFING", "WEEZING", "RHYHORN", "RHYDON", "CHANSEY", "TANGELA", "KANGASKHAN", "HORSEA", "SEADRA", "GOLDEEN", "SEAKING", "STARYU", "STARMIE", "MR. MIME", "SCYTHER", "JYNX", "ELECTABUZZ", "MAGMAR", "PINSIR", "TAUROS", "MAGIKARP", "GYARADOS", "LAPRAS", "DITTO", "EEVEE", "VAPOREON", "JOLTEON", "FLAREON", "PORYGON", "OMANYTE", "OMASTAR", "KABUTO", "KABUTOPS", "AERODACTYL", "SNORLAX", "ARTICUNO", "ZAPDOS", "MOLTRES", "DRATINI", "DRAGONAIR", "DRAGONITE", "MEWTWO", "MEW", "CHIKORITA", "BAYLEEF", "MEGANIUM", "CYNDAQUIL", "QUILAVA", "TYPHLOSION", "TOTODILE", "CROCONAW", "FERALIGATR", "SENTRET", "FURRET", "HOOTHOOT", "NOCTOWL", "LEDYBA", "LEDIAN", "SPINARAK", "ARIADOS", "CROBAT", "CHINCHOU", "LANTURN", "PICHU", "CLEFFA", "IGGLYBUFF", "TOGEPI", "TOGETIC", "NATU", "XATU", "MAREEP", "FLAAFFY", "AMPHAROS", "BELLOSSOM", "MARILL", "AZUMARILL", "SUDOWOODO", "POLITOED", "HOPPIP", "SKIPLOOM", "JUMPLUFF", "AIPOM", "SUNKERN", "SUNFLORA", "YANMA", "WOOPER", "QUAGSIRE", "ESPEON", "UMBREON", "MURKROW", "SLOWKING", "MISDREAVUS", "UNOWN", "WOBBUFFET", "GIRAFARIG", "PINECO", "FORRETRESS", "DUNSPARCE", "GLIGAR", "STEELIX", "SNUBBULL", "GRANBULL", "QWILFISH", "SCIZOR", "SHUCKLE", "HERACROSS", "SNEASEL", "TEDDIURSA", "URSARING", "SLUGMA", "MAGCARGO", "SWINUB", "PILOSWINE", "CORSOLA", "REMORAID", "OCTILLERY", "DELIBIRD", "MANTINE", "SKARMORY", "HOUNDOUR", "HOUNDOOM", "KINGDRA", "PHANPY", "DONPHAN", "PORYGON2", "STANTLER", "SMEARGLE", "TYROGUE", "HITMONTOP", "SMOOCHUM", "ELEKID", "MAGBY", "MILTANK", "BLISSEY", "RAIKOU", "ENTEI", "SUICUNE", "LARVITAR", "PUPITAR", "TYRANITAR", "LUGIA", "HO_OH", "CELEBI", "TREECKO", "GROVYLE", "SCEPTILE", "TORCHIC", "COMBUSKEN", "BLAZIKEN", "MUDKIP", "MARSHTOMP", "SWAMPERT", "POOCHYENA", "MIGHTYENA", "ZIGZAGOON", "LINOONE", "WURMPLE", "SILCOON", "BEAUTIFLY", "CASCOON", "DUSTOX", "LOTAD", "LOMBRE", "LUDICOLO", "SEEDOT", "NUZLEAF", "SHIFTRY", "TAILLOW", "SWELLOW", "WINGULL", "PELIPPER", "RALTS", "KIRLIA", "GARDEVOIR", "SURSKIT", "MASQUERAIN", "SHROOMISH", "BRELOOM", "SLAKOTH", "VIGOROTH", "SLAKING", "NINCADA", "NINJASK", "SHEDINJA", "WHISMUR", "LOUDRED", "EXPLOUD", "MAKUHITA", "HARIYAMA", "AZURILL", "NOSEPASS", "SKITTY", "DELCATTY", "SABLEYE", "MAWILE", "ARON", "LAIRON", "AGGRON", "MEDITITE", "MEDICHAM", "ELECTRIKE", "MANECTRIC", "PLUSLE", "MINUN", "VOLBEAT", "ILLUMISE", "ROSELIA", "GULPIN", "SWALOT", "CARVANHA", "SHARPEDO", "WAILMER", "WAILORD", "NUMEL", "CAMERUPT", "TORKOAL", "SPOINK", "GRUMPIG", "SPINDA", "TRAPINCH", "VIBRAVA", "FLYGON", "CACNEA", "CACTURNE", "SWABLU", "ALTARIA", "ZANGOOSE", "SEVIPER", "LUNATONE", "SOLROCK", "BARBOACH", "WHISCASH", "CORPHISH", "CRAWDAUNT", "BALTOY", "CLAYDOL", "LILEEP", "CRADILY", "ANORITH", "ARMALDO", "FEEBAS", "MILOTIC", "CASTFORM", "KECLEON", "SHUPPET", "BANETTE", "DUSKULL", "DUSCLOPS", "TROPIUS", "CHIMECHO", "ABSOL", "WYNAUT", "SNORUNT", "GLALIE", "SPHEAL", "SEALEO", "WALREIN", "CLAMPERL", "HUNTAIL", "GOREBYSS", "RELICANTH", "LUVDISC", "BAGON", "SHELGON", "SALAMENCE", "BELDUM", "METANG", "METAGROSS", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
  // PT
  { "?", "BULBASAUR", "IVYSAUR", "VENUSAUR", "CHARMANDER", "CHARMELEON", "CHARIZARD", "SQUIRTLE", "WARTORTLE", "BLASTOISE", "CATERPIE", "METAPOD", "BUTTERFREE", "WEEDLE", "KAKUNA", "BEEDRILL", "PIDGEY", "PIDGEOTTO", "PIDGEOT", "RATTATA", "RATICATE", "SPEAROW", "FEAROW", "EKANS", "ARBOK", "PIKACHU", "RAICHU", "SANDSHREW", "SANDSLASH", "NIDORAN F", "NIDORINA", "NIDOQUEEN", "NIDORAN M", "NIDORINO", "NIDOKING", "CLEFAIRY", "CLEFABLE", "VULPIX", "NINETALES", "JIGGLYPUFF", "WIGGLYTUFF", "ZUBAT", "GOLBAT", "ODDISH", "GLOOM", "VILEPLUME", "PARAS", "PARASECT", "VENONAT", "VENOMOTH", "DIGLETT", "DUGTRIO", "MEOWTH", "PERSIAN", "PSYDUCK", "GOLDUCK", "MANKEY", "PRIMEAPE", "GROWLITHE", "ARCANINE", "POLIWAG", "POLIWHIRL", "POLIWRATH", "ABRA", "KADABRA", "ALAKAZAM", "MACHOP", "MACHOKE", "MACHAMP", "BELLSPROUT", "WEEPINBELL", "VICTREEBEL", "TENTACOOL", "TENTACRUEL", "GEODUDE", "GRAVELER", "GOLEM", "PONYTA", "RAPIDASH", "SLOWPOKE", "SLOWBRO", "MAGNEMITE", "MAGNETON", "FARFETCHD", "DODUO", "DODRIO", "SEEL", "DEWGONG", "GRIMER", "MUK", "SHELLDER", "CLOYSTER", "GASTLY", "HAUNTER", "GENGAR", "ONIX", "DROWZEE", "HYPNO", "KRABBY", "KINGLER", "VOLTORB", "ELECTRODE", "EXEGGCUTE", "EXEGGUTOR", "CUBONE", "MAROWAK", "HITMONLEE", "HITMONCHAN", "LICKITUNG", "KOFFING", "WEEZING", "RHYHORN", "RHYDON", "CHANSEY", "TANGELA", "KANGASKHAN", "HORSEA", "SEADRA", "GOLDEEN", "SEAKING", "STARYU", "STARMIE", "MR. MIME", "SCYTHER", "JYNX", "ELECTABUZZ", "MAGMAR", "PINSIR", "TAUROS", "MAGIKARP", "GYARADOS", "LAPRAS", "DITTO", "EEVEE", "VAPOREON", "JOLTEON", "FLAREON", "PORYGON", "OMANYTE", "OMASTAR", "KABUTO", "KABUTOPS", "AERODACTYL", "SNORLAX", "ARTICUNO", "ZAPDOS", "MOLTRES", "DRATINI", "DRAGONAIR", "DRAGONITE", "MEWTWO", "MEW", "CHIKORITA", "BAYLEEF", "MEGANIUM", "CYNDAQUIL", "QUILAVA", "TYPHLOSION", "TOTODILE", "CROCONAW", "FERALIGATR", "SENTRET", "FURRET", "HOOTHOOT", "NOCTOWL", "LEDYBA", "LEDIAN", "SPINARAK", "ARIADOS", "CROBAT", "CHINCHOU", "LANTURN", "PICHU", "CLEFFA", "IGGLYBUFF", "TOGEPI", "TOGETIC", "NATU", "XATU", "MAREEP", "FLAAFFY", "AMPHAROS", "BELLOSSOM", "MARILL", "AZUMARILL", "SUDOWOODO", "POLITOED", "HOPPIP", "SKIPLOOM", "JUMPLUFF", "AIPOM", "SUNKERN", "SUNFLORA", "YANMA", "WOOPER", "QUAGSIRE", "ESPEON", "UMBREON", "MURKROW", "SLOWKING", "MISDREAVUS", "UNOWN", "WOBBUFFET", "GIRAFARIG", "PINECO", "FORRETRESS", "DUNSPARCE", "GLIGAR", "STEELIX", "SNUBBULL", "GRANBULL", "QWILFISH", "SCIZOR", "SHUCKLE", "HERACROSS", "SNEASEL", "TEDDIURSA", "URSARING", "SLUGMA", "MAGCARGO", "SWINUB", "PILOSWINE", "CORSOLA", "REMORAID", "OCTILLERY", "DELIBIRD", "MANTINE", "SKARMORY", "HOUNDOUR", "HOUNDOOM", "KINGDRA", "PHANPY", "DONPHAN", "PORYGON2", "STANTLER", "SMEARGLE", "TYROGUE", "HITMONTOP", "SMOOCHUM", "ELEKID", "MAGBY", "MILTANK", "BLISSEY", "RAIKOU", "ENTEI", "SUICUNE", "LARVITAR", "PUPITAR", "TYRANITAR", "LUGIA", "HO_OH", "CELEBI", "TREECKO", "GROVYLE", "SCEPTILE", "TORCHIC", "COMBUSKEN", "BLAZIKEN", "MUDKIP", "MARSHTOMP", "SWAMPERT", "POOCHYENA", "MIGHTYENA", "ZIGZAGOON", "LINOONE", "WURMPLE", "SILCOON", "BEAUTIFLY", "CASCOON", "DUSTOX", "LOTAD", "LOMBRE", "LUDICOLO", "SEEDOT", "NUZLEAF", "SHIFTRY", "TAILLOW", "SWELLOW", "WINGULL", "PELIPPER", "RALTS", "KIRLIA", "GARDEVOIR", "SURSKIT", "MASQUERAIN", "SHROOMISH", "BRELOOM", "SLAKOTH", "VIGOROTH", "SLAKING", "NINCADA", "NINJASK", "SHEDINJA", "WHISMUR", "LOUDRED", "EXPLOUD", "MAKUHITA", "HARIYAMA", "AZURILL", "NOSEPASS", "SKITTY", "DELCATTY", "SABLEYE", "MAWILE", "ARON", "LAIRON", "AGGRON", "MEDITITE", "MEDICHAM", "ELECTRIKE", "MANECTRIC", "PLUSLE", "MINUN", "VOLBEAT", "ILLUMISE", "ROSELIA", "GULPIN", "SWALOT", "CARVANHA", "SHARPEDO", "WAILMER", "WAILORD", "NUMEL", "CAMERUPT", "TORKOAL", "SPOINK", "GRUMPIG", "SPINDA", "TRAPINCH", "VIBRAVA", "FLYGON", "CACNEA", "CACTURNE", "SWABLU", "ALTARIA", "ZANGOOSE", "SEVIPER", "LUNATONE", "SOLROCK", "BARBOACH", "WHISCASH", "CORPHISH", "CRAWDAUNT", "BALTOY", "CLAYDOL", "LILEEP", "CRADILY", "ANORITH", "ARMALDO", "FEEBAS", "MILOTIC", "CASTFORM", "KECLEON", "SHUPPET", "BANETTE", "DUSKULL", "DUSCLOPS", "TROPIUS", "CHIMECHO", "ABSOL", "WYNAUT", "SNORUNT", "GLALIE", "SPHEAL", "SEALEO", "WALREIN", "CLAMPERL", "HUNTAIL", "GOREBYSS", "RELICANTH", "LUVDISC", "BAGON", "SHELGON", "SALAMENCE", "BELDUM", "METANG", "METAGROSS", "REGIROCK", "REGICE", "REGISTEEL", "LATIAS", "LATIOS", "KYOGRE", "GROUDON", "RAYQUAZA", "JIRACHI", "DEOXYS" },
};

// el primer huevo de la partida: iniciales clasicos
static const int16_t CLASSIC_DEX[] = { 1, 4, 7, 25, 133 };
#define NUM_CLASSIC_DEX 5
