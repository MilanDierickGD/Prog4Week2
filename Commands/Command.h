#pragma once
#include <iostream>

#include "GameActor.h"

namespace DAE
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(GameActor& actor) = 0;
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute(GameActor& actor) override { actor.Jump(); }
	};

	class FireCommand final : public Command
	{
	public:
		void Execute(GameActor& actor) override { actor.FireGun(); }
	};

	class DuckCommand final : public Command
	{
	public:
		void Execute(GameActor& actor) override { actor.Duck(); }
	};

	class FartCommand final : public Command
	{
	public:
		void Execute(GameActor& actor) override { actor.Fart(); }
	};
}
