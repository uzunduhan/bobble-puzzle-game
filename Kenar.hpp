#pragma once

#include "Cizilebilir.hpp"
#include<SFML/Graphics.hpp>
class Kenar :public Cizilebilir
{
public:
	Kenar();
	void ayarla(float boyut, float x, float y);
	// Inherited via Cizilebilir
	virtual void ciz(Pencere& pencere) override;

	sf::RectangleShape	m_ustYatayCizgi;
	sf::RectangleShape	m_altYatayCizgi;
	sf::RectangleShape	m_solDikeyCizgi;
	sf::RectangleShape	m_sagDikeyCizgi;
	sf::RectangleShape	m_blok;
	int					m_cizgiSayisi;
	float				m_mesafe;
	sf::Vector2f		m_konum;
};