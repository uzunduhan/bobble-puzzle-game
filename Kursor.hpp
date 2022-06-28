#pragma once

#include "Cizilebilir.hpp"
#include "TemelTurler.hpp"
#include <SFML/Graphics.hpp>

class Kursor : public Cizilebilir
{
public:
	Kursor();
	void ayarla(float boyut);
	void yonDegistir(YON yeniYon);
	void hareket();
	virtual void ciz(Pencere& pencere) override;



	sf::RectangleShape	m_kursor;
	float				m_mesafe;
	sf::Vector2f		m_konum;
	YON					m_siradakiYon;
private:
	KaplamaHaritasi		m_aracKaplamaListesi;
};
