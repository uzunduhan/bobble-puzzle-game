#include "Kenar.hpp"
#include "Pencere.hpp"
Kenar::Kenar()
{

}

void Kenar::ayarla(float boyut, float x, float y)
{
	m_ustYatayCizgi.setSize(sf::Vector2f(485.f, 1.f));
	m_altYatayCizgi.setSize(sf::Vector2f(485.f, 1.f));
	m_solDikeyCizgi.setSize(sf::Vector2f(1.f, 695.f));
	m_sagDikeyCizgi.setSize(sf::Vector2f(1.f, 695.f));
	m_blok.setSize(sf::Vector2f(x, y));

	m_ustYatayCizgi.setPosition(sf::Vector2f(67.f, 67.f));
	m_altYatayCizgi.setPosition(sf::Vector2f(67.f, 762.f));
	m_solDikeyCizgi.setPosition(sf::Vector2f(67.f, 67.f));
	m_sagDikeyCizgi.setPosition(sf::Vector2f(552.f, 67.f));
	m_blok.setPosition(sf::Vector2f(67.0f, 67.0f));
}
void Kenar::ciz(Pencere& pencere)
{
	pencere.ciz(m_ustYatayCizgi);
	pencere.ciz(m_altYatayCizgi);
	pencere.ciz(m_solDikeyCizgi);
	pencere.ciz(m_sagDikeyCizgi);
	pencere.ciz(m_blok);
}
