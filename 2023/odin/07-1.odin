package main

import "core:fmt"
import "core:os"
import "core:slice"
import "core:sort"
import "core:strconv"
import "core:strings"

Type :: enum {
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	FIVE_OF_A_KIND,
}

Hand :: struct {
	cards: string,
	bid:   int,
	type:  Type,
}

card_strength_map: map[u8]int

populate_card_strength_map :: proc() {
	card_strength_map['2'] = 2
	card_strength_map['3'] = 3
	card_strength_map['4'] = 4
	card_strength_map['5'] = 5
	card_strength_map['6'] = 6
	card_strength_map['7'] = 7
	card_strength_map['8'] = 8
	card_strength_map['9'] = 9
	card_strength_map['T'] = 10
	card_strength_map['J'] = 11
	card_strength_map['Q'] = 12
	card_strength_map['K'] = 13
	card_strength_map['A'] = 14
}

compare_hand :: proc(a: Hand, b: Hand) -> bool {
	if a.type != b.type do return a.type < b.type
	for i := 0; i < 5; i += 1 {
		if a.cards[i] == b.cards[i] do continue
		ac := a.cards[i]
		bc := b.cards[i]
		return card_strength_map[ac] < card_strength_map[bc]
	}
	return false
}

get_type :: proc(card: string) -> Type {
	count: [128]int
	for ch, idx in card do count[ch] += 1
	two, three, four, five := 0, 0, 0, 0
	for i := 0; i < 128; i += 1 {
		two += count[i] == 2 ? 1 : 0
		three += count[i] == 3 ? 1 : 0
		four += count[i] == 4 ? 1 : 0
		five += count[i] == 5 ? 1 : 0
	}
	if five == 1 do return Type.FIVE_OF_A_KIND
	else if four == 1 do return Type.FOUR_OF_A_KIND
	else if three == 1 && two == 1 do return Type.FULL_HOUSE
	else if three == 1 do return Type.THREE_OF_A_KIND
	else if two == 2 do return Type.TWO_PAIR
	else if two == 1 do return Type.ONE_PAIR
	else do return Type.HIGH_CARD
}

convert_to_hand :: proc(card: string) -> Hand {
	hand: Hand
	tokens := strings.split(card, " ")
	hand.cards = strings.clone(tokens[0])
	hand.bid = strconv.atoi(tokens[1])
	hand.type = get_type(hand.cards)
	return hand
}

read_all_hands :: proc(filepath: string) -> [dynamic]Hand {
	data, ok := os.read_entire_file(filepath, context.allocator)
	defer delete(data, context.allocator)
	it := string(data)
	result: [dynamic]Hand
	for line in strings.split_lines_iterator(&it) {
		hand := convert_to_hand(line)
		append(&result, hand)
	}
	return result
}

main :: proc() {
	populate_card_strength_map()
	hands := read_all_hands("in.txt")
	slice.sort_by(hands[:], compare_hand)
	result := 0
	for hand, idx in hands {
		result += (idx + 1) * hand.bid
		fmt.println(hand)
	}
	fmt.println(result)
}
