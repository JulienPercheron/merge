#include "Raven_TargetingSystem.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"



//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem::Raven_TargetingSystem(Raven_Bot* owner):m_pOwner(owner),
                                                               m_pCurrentTarget(0),
															   m_pPrimaryTarget(0)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem::Update()
{
  double ClosestDistSoFar = MaxDouble;
  m_pCurrentTarget       = 0;

  //S'il n'y a pas de cible prioritaire, on tape sur tout ce qui bouge. Sinon on va la traquer
  //jusqu'à ce qu'il n'y ait plus de cible prioritaire (quand elle meurt par exemple)
  if (!m_pPrimaryTarget) {
	  //grab a list of all the opponents the owner can sense
	  std::list<Raven_Bot*> SensedBots;
	  SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

	  std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	  for (curBot; curBot != SensedBots.end(); ++curBot)
	  {
		  //make sure the bot is alive and that it is not the owner and not in the same team
		  if ((*curBot)->isAlive() && (*curBot != m_pOwner) && IsInSameTeam(*curBot, m_pOwner)){
			  double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

			  if (dist < ClosestDistSoFar)
			  {
				  ClosestDistSoFar = dist;
				  m_pCurrentTarget = *curBot;
			  }
		  }
	  }
  }
  else {
	  m_pCurrentTarget = m_pPrimaryTarget;
  }
  
}

bool Raven_TargetingSystem::IsInSameTeam(Raven_Bot* bot1, Raven_Bot* bot2)const {//----------------------------------Nouvelle méthode
	if (bot1->GetTeam() && bot2->GetTeam()) {
		if (bot1->GetTeam()->GetName().compare(bot2->GetTeam()->GetName()) == 0) {
			return false;
		}
	}
	return true;
}


bool Raven_TargetingSystem::isTargetWithinFOV()const
{
  return m_pOwner->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
}

bool Raven_TargetingSystem::isTargetShootable()const
{
  return m_pOwner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
}

Vector2D Raven_TargetingSystem::GetLastRecordedPosition()const
{
  return m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenVisible()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenOutOfView()const
{
  return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
}