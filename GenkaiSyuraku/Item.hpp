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
	"","石材","木材","鉱石","金塊","ワラ",
	"小魚","中魚","大魚","マンボウ","ジンベイザメ","リュウグウノツカイ",
	"ホウキ","トマト種","キャベツ種","トウモロコシ種","トマト","キャベツ","トウモロコシ"
};

std::array<std::string, item_num> item_string{
   "",
   "タワーや城を建築するために必要な素材。\n広場で入手可能。",
   "牧場の増築に必要な素材。\n広場で入手可能。",
   "城やタワーの増築に必要な素材。\n広場で入手可能。",
   "よろず屋で高く売れる。広場で入手可能。",
   "牧場の増築に必要な素材。\n広場で入手可能。",
   "よく釣れる魚。",
   "そこそこよく釣れる魚。",
   "そこそこ釣れる魚。",
   "たまに釣れる魚。",
   "ごくまれに釣れる魚。",
   "ごくたまに釣れる魚。",
   "広場の素材集めを効率的に行うための道具。\nよろず屋で買うことができる",
   "畑でトマトを育てるのに必要な種。\nよろず屋で買うことができる。",
   "畑でキャベツを育てるのに必要な種。\nよろず屋で買うことができる。",
   "畑でトウモロコシを育てるのに必要な種。\nよろず屋で買うことができる。",
   "畑で収穫されたトマト。\nよろず屋で売ることができる。",
   "畑で収穫されたキャベツ。\nよろず屋で売ることができる。",
   "畑で収穫されたトウモロコシ。\nよろず屋で売ることができる。"
};
