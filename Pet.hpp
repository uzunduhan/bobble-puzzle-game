#pragma once
#include "Cizilebilir.hpp"
#include "AnimasyonPet.hpp"
#include "TemelTurler.hpp"
#include <string>

class Oyun;
class Pet :public Cizilebilir
{
public:
	Pet(const std::string& fileName, Oyun* oyun);
	void guncelle(float gecenSure);
	void tusBasildi(sf::Keyboard::Key tus);
	void tusBirakma(sf::Keyboard::Key tus);
	void animasyonDegistir(const std::string& yeniAnimasyon);
	void yonDegistir(const std::string& yeniYon);
	virtual void ciz(Pencere& pencere) override;

private:
	std::string						m_aktifAnimasyon;
	std::string						m_aktifYon;
	TexturePtr						m_kaplama;
	PetYonluAnimasyonHaritasi		m_animasyonlar;

	// Inherited via Cizilebilir

};
typedef std::shared_ptr<Pet>	PetPtr;