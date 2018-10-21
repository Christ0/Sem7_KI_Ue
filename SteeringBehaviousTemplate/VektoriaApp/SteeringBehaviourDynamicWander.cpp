#include "SteeringBehaviourDynamicWander.h"



SteeringBehaviourDynamicWander::SteeringBehaviourDynamicWander(Spielfeld * aspielfeld) {
	m_spielfeld = aspielfeld;
	m_boid = NULL;
	m_targetgroup = NULL;
	m_radius = 5.f;
	m_offset = 5.f;
	m_maxRichtungsaenderung = DEGREES_TO_RADIANS(10);
	m_winkelAenderung = 0;

	m_facemode = MOVEDIRECTION;
}

SteeringBehaviourDynamicWander::~SteeringBehaviourDynamicWander()
{
}

Steuerung SteeringBehaviourDynamicWander::update(Boid * aboid, std::vector<Boid*>* atarget) {
	Steuerung ergSteuerung;
	CHVector positionsMittelpunkt = angletovector(m_kinematikBoid->orientierung) * m_offset;
	float prozent1 = (rand() % 100) / 100.f;
	float prozent2 = (rand() % 100) / 100.f;
	float prozent = 1 - (prozent1 + prozent2);

	m_winkelAenderung += prozent * m_maxRichtungsaenderung;
	m_positionAufKreis = positionsMittelpunkt + angletovector(m_winkelAenderung).Normal() * m_radius;

	ergSteuerung.linear = m_positionAufKreis * aboid->getMaxSteuerungsKraft();
	ergSteuerung.angular = 0.f;
	return ergSteuerung;

}
