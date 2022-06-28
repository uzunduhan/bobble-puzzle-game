#pragma once
#include "Cizilebilir.hpp"
#include "Animasyon.hpp"
#include "TemelTurler.hpp"
#include <string>

class Oyun;
class AnimKursor :public Cizilebilir
{
public:
	AnimKursor(const std::string& fileName, Oyun* oyun);
	virtual void ciz(Pencere& pencere) override;
	void animKursorHareket();

private:
	std::string				m_aktifAnimasyon;
	std::string				m_aktifYon;
	TexturePtr				m_kaplama;
	YonluAnimasyonHaritasi	m_animasyonlar;

	// Inherited via Cizilebilir

};
typedef std::shared_ptr<AnimKursor>	AnimKursorPtr;