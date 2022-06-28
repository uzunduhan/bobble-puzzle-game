#include "Kursor.hpp"
#include "Pencere.hpp"
#include <iostream>

Kursor::Kursor()
{
	m_siradakiYon = YON::YON_YUKARI;
}



void Kursor::ayarla(float boyut)
{
	m_kursor.setSize(sf::Vector2f(1.f, 50.f));
	m_kursor.setPosition(sf::Vector2f(287.5f, 662.5f));
	m_kursor.setRotation(sf::degrees(180.f));
	m_kursor.setFillColor(sf::Color::Transparent);

}

void Kursor::ciz(Pencere& pencere)
{
	pencere.ciz(m_kursor);
}

void Kursor::yonDegistir(YON yeniYon)
{
	if (yeniYon == YON::YON_SAG)
		return;
	if (yeniYon == YON::YON_SOL)
		return;
	m_siradakiYon = yeniYon;

}

void Kursor::hareket()
{
	if (m_kursor.getRotation().asDegrees() < 265)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_kursor.rotate(sf::degrees(1.f));
		}
	}


	//std::cout << m_cizgi.getRotation() << std::endl;


	if (m_kursor.getRotation().asDegrees() > 95)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_kursor.rotate(sf::degrees(-1.f));
		}
	}
	//std::cout << m_kursor.getRotation().asDegrees() << std::endl;

}