#include "Raven_Team.h"
#include "Messaging/Telegram.h"
#include "Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"

Raven_Team::Raven_Team(Raven_Game* world, const std::string& pName, int pTeamSize):
	m_name(pName),
	m_pWorld(world)
{
	for (int i = 0; i < pTeamSize; i++) {
		AddPlayer();
	}
	this->m_isInOffset = false;

}


Raven_Team::~Raven_Team()
{
}

void Raven_Team::AddPlayer() {
	this->m_pWorld->AddBots(1);
	this->m_Players.push_back(m_pWorld->GetAllBots().back());
	m_pWorld->GetAllBots().back()->SetTeam(this);
}

void Raven_Team::DeletePlayer() {
	
}



void Raven_Team::Communicate_NewTarget(Raven_Bot* target)
{
	std::list<Raven_Bot*>::const_iterator curBot = this->m_Players.begin();
	for (curBot; curBot != m_Players.end(); ++curBot)
	{
		Raven_Bot* botCourant = *curBot;

		if (!botCourant->isPossessed()) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				m_pWorld->PossessedBot()->ID(),
				botCourant->ID(),
				Msg_TeamNewTarget,
				target);
		}
		
	}
}

void Raven_Team::Communicate_DeathOfTarget(Raven_Bot* killer)
{
	std::list<Raven_Bot*>::const_iterator curBot = this->m_Players.begin();
	for (curBot; curBot != m_Players.end(); ++curBot)
	{
		Raven_Bot* botCourant = *curBot;

		if (!botCourant->isPossessed()) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				killer->ID(),
				botCourant->ID(),
				Msg_TeamDeadTarget,
				NO_ADDITIONAL_INFO);
		}

	}
}

void Raven_Team::ApplyOffsetPursuit() {
	std::list<Raven_Bot*>::const_iterator curBot = this->m_Players.begin();
	Raven_Bot* followedAgent = m_pWorld->PossessedBot();
	int iteration = 0;
	for (curBot; curBot != m_Players.end(); ++curBot)
	{
		iteration++;
		Raven_Bot* botCourant = *curBot;
		if (!botCourant->isPossessed()) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				m_pWorld->PossessedBot()->ID(),
				botCourant->ID(),
				Msg_OffsetOn,
				&iteration);
		}
	}
	SwapOffsetStatus();
}

void Raven_Team::DisableOffsetPursuit() {
	std::list<Raven_Bot*>::const_iterator curBot = this->m_Players.begin();

	for (curBot; curBot != m_Players.end(); ++curBot)
	{
		Raven_Bot* botCourant = *curBot;

		if (!botCourant->isPossessed()) {
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
				m_pWorld->PossessedBot()->ID(),
				botCourant->ID(),
				Msg_OffsetOff,
				NO_ADDITIONAL_INFO);
		}
	}

	SwapOffsetStatus();
}