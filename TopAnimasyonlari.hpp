#pragma once

#include "Cizilebilir.hpp"
#include "TemelTurler.hpp"

class TopAnimasyonlari :public Cizilebilir
{
public:
	TopAnimasyonlari();
	void olustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi);
	void guncelle();


	std::vector<sf::Sprite> m_spriteListesi;
	int			m_aktifSprite;
	int			m_degisimSuresi;
	int			m_sayac;
	std::string	m_aktifRenk;

	virtual void ciz(Pencere& pencere) override;
};
typedef std::shared_ptr<TopAnimasyonlari> TopAnimasyonlariPtr;
typedef std::map<std::string, TopAnimasyonlariPtr> TopAnimasyonlariHaritasi;
typedef std::map<std::string, TopAnimasyonlariHaritasi> TopRenkliAnimasyonlarHaritasi;
