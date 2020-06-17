#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

namespace rda
{
	enum class choice : uint8_t
	{
		YES = 1,
		NO = 2,
		INVALID = 3
	};

	class state
	{
	public:
		state() = default;
		virtual ~state() = default;
		virtual choice run() = 0;
	};

	class decision_state : public state
	{
	public:
		decision_state(std::string&& question, std::string&& yes_choice, std::string&& no_choice)
			: m_question(std::move(question)), m_yes_choice(std::move(yes_choice)), m_no_choice(std::move(no_choice))
		{
		}

		virtual choice run() override
		{
			choice c = choice::INVALID;

			while (c == choice::INVALID)
			{
				std::cout << std::endl << m_question << std::endl;
				std::cout << "1) " << m_yes_choice << std::endl;
				std::cout << "2) " << m_no_choice << std::endl;
				std::cout << "Enter 1 or 2: ";

				std::string text;
				std::cin >> text;

				if (!text.empty())
				{
					if (text[0] == '1')
						c = choice::YES;
					else if (text[0] == '2')
						c = choice::NO;
				}
			}

			return c;
		}

	private:
		const std::string m_question;
		const std::string m_yes_choice;
		const std::string m_no_choice;
	};

	class answer_state : public state
	{
	public:
		answer_state(std::string&& answer)
			: m_answer(std::move(answer))
		{
		}

		virtual choice run() override
		{
			std::cout << std::endl << "Answer:" << std::endl;
			std::cout << m_answer << std::endl;			
			return rda::choice::INVALID;
		}

	private:
		std::string m_answer;
	};
}