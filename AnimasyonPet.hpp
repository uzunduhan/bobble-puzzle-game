#pragma once

#include "Cizilebilir.hpp"
#include "TemelTurler.hpp"

class AnimasyonPet :public Cizilebilir
{
public:
	AnimasyonPet();
	void petOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi);
	void petiTerstenOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi);
	void petGuncelle();


	std::vector<sf::Sprite> m_spriteListesi;
	int			m_aktifSprite;
	int			m_degisimSuresi;
	int			m_sayac;
	std::string	m_aktifYon;

	virtual void ciz(Pencere& pencere) override;
};
typedef std::shared_ptr<AnimasyonPet> AnimasyonPetPtr;
typedef std::map<std::string, AnimasyonPetPtr> PetAnimasyonHaritasi;
typedef std::map<std::string, PetAnimasyonHaritasi> PetYonluAnimasyonHaritasi;