
//
// main.cpp - Program to help you decide which c++ standard library container
// is appropriate for you.
//
// Written by Ryan Antkowiak 
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


#include "state.h"
#include "statemachine.h"


int main()
{
	// decisions
	std::shared_ptr<rda::decision_state> dec_orderimportant(std::make_shared<rda::decision_state>(
		"Is order important?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_lifo(std::make_shared<rda::decision_state>(
		"Last In First Out?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_fifo(std::make_shared<rda::decision_state>(
		"First In First Out?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_bifo(std::make_shared<rda::decision_state>(
		"Best In First Out?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_keepsorted(std::make_shared<rda::decision_state>(
		"Keep sorted elements?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_notordered_lookupkeys(std::make_shared<rda::decision_state>(
		"Look-up keys?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_notordered_lookupkeys_allowdups(std::make_shared<rda::decision_state>(
		"Allow duplicates?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_lookupkeys_noallowdupes_separatekeyvalue(std::make_shared<rda::decision_state>(
		"Separate Key / Value?", "yes", "no"));

	std::shared_ptr<rda::decision_state> dec_ordered_lookupkeys_allowdups_separatekeyvalue(std::make_shared<rda::decision_state>(
		"Separate Key / Value?", "yes", "no"));

	////// answers
	auto ans_stack(std::make_shared<rda::answer_state>("stack"));
	auto ans_queue(std::make_shared<rda::answer_state>("queue"));
	auto ans_priority_queue(std::make_shared<rda::answer_state>("priority_queue"));
	auto ans_unordered_map(std::make_shared<rda::answer_state>("unordered_map"));
	auto ans_unordered_set(std::make_shared<rda::answer_state>("unordered_set"));
	auto ans_unordered_multimap(std::make_shared<rda::answer_state>("unordered_multimap"));
	auto ans_unordered_multiset(std::make_shared<rda::answer_state>("unordered_multiset"));
	auto ans_vector(std::make_shared<rda::answer_state>("vector"));
	auto ans_vector_sorted(std::make_shared<rda::answer_state>("vector (sorted)"));
	auto ans_deque(std::make_shared<rda::answer_state>("deque"));
	auto ans_list(std::make_shared<rda::answer_state>("list"));
	auto ans_map(std::make_shared<rda::answer_state>("map"));
	auto ans_set(std::make_shared<rda::answer_state>("set"));
	auto ans_multimap(std::make_shared<rda::answer_state>("multimap"));
	auto ans_multiset(std::make_shared<rda::answer_state>("multiset"));
	


	// create the state machine
	rda::statemachine<std::shared_ptr<rda::state>, rda::choice> sm(dec_orderimportant);

	// function to be run upon entering any decision state (or answer state)
	auto state_func = [&sm](const std::shared_ptr<rda::state>& from_state, const rda::choice& evt, const std::shared_ptr<rda::state>& to_state)
	{
		rda::choice c = to_state->run();
		if (c != rda::choice::INVALID)
			sm.push_event(c);
	};

	sm.add_state(ans_stack, state_func);
	sm.add_state(ans_queue, state_func);
	sm.add_state(ans_priority_queue, state_func);
	sm.add_state(ans_unordered_map, state_func);
	sm.add_state(ans_unordered_set, state_func);
	sm.add_state(ans_unordered_multimap, state_func);
	sm.add_state(ans_unordered_multiset, state_func);
	sm.add_state(ans_vector, state_func);
	sm.add_state(ans_vector_sorted, state_func);
	sm.add_state(ans_deque, state_func);
	sm.add_state(ans_list, state_func);
	sm.add_state(ans_map, state_func);
	sm.add_state(ans_set, state_func);
	sm.add_state(ans_multimap, state_func);
	sm.add_state(ans_multiset, state_func);

	sm.add_state(dec_ordered_lifo, state_func);
	sm.add_state(dec_ordered_fifo, state_func);
	sm.add_state(dec_ordered_bifo, state_func);
	sm.add_state(dec_ordered_keepsorted, state_func);
	sm.add_state(dec_notordered_lookupkeys, state_func);
	sm.add_state(dec_notordered_lookupkeys_allowdups, state_func);
	sm.add_state(dec_ordered_lookupkeys_noallowdupes_separatekeyvalue, state_func);
	sm.add_state(dec_ordered_lookupkeys_allowdups_separatekeyvalue, state_func);

	sm.add_transition(dec_orderimportant, rda::choice::YES, dec_ordered_lifo);
	sm.add_transition(dec_orderimportant, rda::choice::NO, dec_notordered_lookupkeys);

	sm.add_transition(dec_ordered_lifo, rda::choice::YES, ans_stack);
	sm.add_transition(dec_ordered_lifo, rda::choice::NO, dec_ordered_fifo);

	sm.add_transition(dec_ordered_fifo, rda::choice::YES, ans_queue);
	sm.add_transition(dec_ordered_fifo, rda::choice::NO, dec_ordered_bifo);

	sm.add_transition(dec_ordered_bifo, rda::choice::YES, ans_priority_queue);
	sm.add_transition(dec_ordered_bifo, rda::choice::NO, dec_ordered_keepsorted);

	sm.add_transition(dec_notordered_lookupkeys, rda::choice::YES, dec_notordered_lookupkeys_allowdups);
	// FIXME add NO

	sm.add_transition(dec_notordered_lookupkeys_allowdups, rda::choice::YES, dec_ordered_lookupkeys_allowdups_separatekeyvalue);
	sm.add_transition(dec_notordered_lookupkeys_allowdups, rda::choice::NO, dec_ordered_lookupkeys_noallowdupes_separatekeyvalue);

	sm.add_transition(dec_ordered_lookupkeys_allowdups_separatekeyvalue, rda::choice::YES, ans_unordered_multimap);
	sm.add_transition(dec_ordered_lookupkeys_allowdups_separatekeyvalue, rda::choice::NO, ans_unordered_multiset);

	sm.add_transition(dec_ordered_lookupkeys_noallowdupes_separatekeyvalue, rda::choice::YES, ans_unordered_map);
	sm.add_transition(dec_ordered_lookupkeys_noallowdupes_separatekeyvalue, rda::choice::NO, ans_unordered_set);


	// run the state machine
	state_func(dec_orderimportant, rda::choice::INVALID, dec_orderimportant);
	sm.run();

	return EXIT_SUCCESS;
}