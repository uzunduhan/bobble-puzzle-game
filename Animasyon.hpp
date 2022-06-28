#pragma once
#include "Cizilebilir.hpp"
#include "TemelTurler.hpp"
class Animasyon :public Cizilebilir
{
public:
	Animasyon();

	void carkOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi);
	void animKursorOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi);



	std::vector<sf::Sprite> m_spriteListesi;
	int		m_aktifSprite;
	int		m_degisimSuresi;
	int		m_sayac;
	std::string	m_aktifYon;
	std::string	m_aktifRenk;
	// Inherited via Cizilebilir
	virtual void ciz(Pencere& pencere) override;
};
typedef std::shared_ptr<Animasyon> AnimasyonPtr;
typedef std::map<std::string, AnimasyonPtr> AnimasyonHaritasi;
typedef std::map<std::string, AnimasyonHaritasi> YonluAnimasyonHaritasi;