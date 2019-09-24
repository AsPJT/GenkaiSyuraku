#pragma once

#include <cstdint>
#include <array>
#include <string>

enum :std::uint_fast8_t {
	// 空白
	item_empty,
	// 石材
	item_stone,
	// 木材
	item_wood,
	// 鉱石
	item_ore,
	//金塊
	item_gold,
	// ワラ
	item_straw,
	// 小魚
	item_fish_small,
	// 中魚
	item_fish_medium,
	// 大魚
	item_fish_large,
	// マンボウ
	item_fish_sunfish,
	// ジンベイザメ
	item_fish_whale_shark,
	// リュウグウノツカイ
	item_fish_regalecus_glesne,
	// ほうき
	item_broom,
	// とまと種
	item_tomato_seed,
	// きゃべつ種
	item_cabbage_seed,
	// とうもろこし種
	item_corn_seed,
	// とまと
	item_tomato,
	// きゃべつ
	item_cabbage,
	// とうもろこし
	item_corn,
	// 合計数
	item_num
};

std::array<std::string, item_num> item_name{
	u8"",u8"石材",u8"木材",u8"鉱石",u8"金塊",u8"ワラ",
	u8"小魚",u8"中魚",u8"大魚",u8"マンボウ",u8"ジンベイザメ",u8"リュウグウノツカイ",
	u8"ホウキ",u8"トマト種",u8"キャベツ種",u8"トウモロコシ種",u8"トマト",u8"キャベツ",u8"トウモロコシ"
};

std::array<std::string, item_num> item_string{
   u8"",
   u8"タワーや城を建築するために必要な素材。\n広場で入手可能。",
   u8"牧場の増築に必要な素材。\n広場で入手可能。",
   u8"城やタワーの増築に必要な素材。\n広場で入手可能。",
   u8"よろず屋で高く売れる。広場で入手可能。",
   u8"牧場の増築に必要な素材。\n広場で入手可能。",
   u8"よく釣れる魚。",
   u8"そこそこよく釣れる魚。",
   u8"そこそこ釣れる魚。",
   u8"たまに釣れる魚。",
   u8"ごくまれに釣れる魚。",
   u8"ごくたまに釣れる魚。",
   u8"広場の素材集めを効率的に行うための道具。\nよろず屋で買うことができる",
   u8"畑でトマトを育てるのに必要な種。\nよろず屋で買うことができる。",
   u8"畑でキャベツを育てるのに必要な種。\nよろず屋で買うことができる。",
   u8"畑でトウモロコシを育てるのに必要な種。\nよろず屋で買うことができる。",
   u8"畑で収穫されたトマト。\nよろず屋で売ることができる。",
   u8"畑で収穫されたキャベツ。\nよろず屋で売ることができる。",
   u8"畑で収穫されたトウモロコシ。\nよろず屋で売ることができる。"
};

std::array<std::uint_fast32_t, item_num> item_buy{
	100,100,100,100,100,100,
	100,100,100,100,100,100,
	100,100,100,100,100,100,100
};


std::array<std::uint_fast32_t, item_num> item_sell{
	100,100,100,100,100,100,
	100,100,100,100,100,100,
	100,100,100,100,100,100,100
};
