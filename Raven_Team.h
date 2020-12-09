#pragma once

#ifndef RAVEN_EQUIPE_H
#define RAVEN_EQUIPE_H

#include <list>
#include <string>

#include "Raven_Bot.h"
#include "Raven_Game.h"

//enum NomEquipe { BLUE, RED, YELLOW, GREEN };

class Raven_Game;
class Raven_Bot;

class Raven_Team
{
private:
	enum TeamColor { RED, BLUE, YELLOW, GREEN };
private:

	Raven_Game* m_pWorld;

	std::list<Raven_Bot*> m_Players;

	Raven_Bot* m_pTarget;

	//NomEquipe m_name;
	std::string m_name;

	TeamColor m_color;

	bool m_isInOffset;

public:
	

	Raven_Team(Raven_Game* world, const std::string& name, int teamSize);
	~Raven_Team();

	void AddPlayer();
	void DeletePlayer();

	void ApplyOffsetPursuit();
	void DisableOffsetPursuit();

	void Communicate_NewTarget(Raven_Bot* target);
	void Communicate_DeathOfTarget(Raven_Bot* killer);

	std::string& GetName() { return m_name; };
	Raven_Bot* GetTarget() { return m_pTarget; }

	void SetColor_BLUE() { this->m_color = TeamColor::BLUE; }
	void SetColor_RED() { this->m_color = TeamColor::RED; }
	void SetColor_YELLOW() { this->m_color = TeamColor::YELLOW; }
	void SetColor_GREEN() { this->m_color = TeamColor::GREEN; }

	int GetColor() { return this->m_color; }
	int GetTeamSize() { return this->m_Players.size(); }
	
	void SwapOffsetStatus() { this->m_isInOffset = !this->m_isInOffset; }
	bool IsInOffset() { return this->m_isInOffset; }
};




#endif

