#pragma once
#include "Cizilebilir.hpp"
#include "TemelTurler.hpp"
#include "TopAnimasyonlari.hpp"
#include <string>
#define PI 3.14159265

class Oyun;
class Top :public Cizilebilir
{
public:
	Top(float cap, sf::Color renk, const std::string& fileName, Oyun* oyun);
	static std::shared_ptr<Top> topUret(float cap, sf::Color renk, const std::string& fileName, Oyun* oyun);
	virtual void ciz(Pencere& pencere) override;
	void firlatma(float aci);



	float			m_boyut;
	float			m_dereceSin;
	float			m_dereceCos;
	float			m_hizX;
	float			m_hizY;

	YON				m_yon;
	RenkDizisi		m_renkDizisi = { sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow };
	sf::CircleShape m_sekil;

	std::string						m_aktifAnimasyon;
	std::string						m_aktifRenk;
	TexturePtr						m_kaplama;
	TopRenkliAnimasyonlarHaritasi		m_animasyonlar;
};
typedef std::shared_ptr<Top>	TopPtr;
typedef std::vector<TopPtr>	TopListesi;