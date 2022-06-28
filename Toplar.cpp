#include "Toplar.hpp"
#include "Pencere.hpp"
#include "Oyun.hpp"

Toplar::Toplar(float cap, float x, float y, const std::string& fileName, Oyun* oyun)
{
	this->m_cap = cap;
	sf::Color tempRenk = sf::Color::Green;
	auto yeniTop = Top::topUret(m_cap, tempRenk, fileName, oyun);
	srand(time(NULL));

	yeniTop->m_sekil.setOrigin(sf::Vector2f(m_cap, m_cap));
	yeniTop->m_konum.x = x;
	yeniTop->m_konum.y = y;
	m_topDizisi.push_back(yeniTop);
}

void Toplar::ciz(Pencere& pencere)
{
	for (auto siradaki : m_topDizisi)
	{
		if (siradaki != m_topDizisi[m_topDizisi.size() - 1])
		{
			siradaki->ciz(pencere);
		}
	}
}

void Toplar::topEkle(float x, float y, const std::string& fileName, Oyun* oyun)
{
	if (m_topDizisi.empty())
		return;

	srand(time(NULL));
	sf::Color tempRenk = m_renkDizisi[rand() % 4];

	auto yeniTop = Top::topUret(m_cap, tempRenk, fileName, oyun);

	yeniTop->m_sekil.setOrigin(sf::Vector2f(m_cap, m_cap));
	yeniTop->m_konum.x = x;
	yeniTop->m_konum.y = y;
	m_topDizisi.push_back(yeniTop);
}