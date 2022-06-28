#pragma once
#include "Top.hpp"
#include <vector>
#include <string.h>

class Oyun;
class Toplar :public Cizilebilir
{
public:
	Toplar(float hucreBoyutu, float x, float y, const std::string& fileName, Oyun* oyun);
	// Inherited via Cizilebilir
	virtual void ciz(Pencere& pencere) override;
	void topEkle(float x, float y, const std::string& fileName, Oyun* oyun);

	RenkDizisi	m_renkDizisi = { sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow };
	TopListesi	m_topDizisi;
	float		m_cap;
};

typedef std::shared_ptr<Toplar> ToplarPtr;
