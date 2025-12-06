/*
 * Interface for the command pattern.
 * Author: H. Hristov
 * 06.12.2025
 */

#pragma once
class Command {
public:
	virtual void Execute() = 0;
	virtual ~Command() = default;
};

