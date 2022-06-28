#include "Animasyon.hpp"
#include "Pencere.hpp"
Animasyon::Animasyon()
{
	m_aktifYon = "Sag";
	m_aktifRenk = "Yesil";
	m_aktifSprite = 0;
	m_sayac = 0;
	m_degisimSuresi = 5;
	m_konum = sf::Vector2f(0.0f, 0.0f);

}

void Animasyon::carkOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi)
{
	sf::Vector2i sonKonum = konum;
	for (int i = 0; i < cerceveSayisi; i++)
	{
		sf::Sprite sprite;

		sprite.setTexture(*kaplama);
		sprite.setTextureRect(sf::IntRect(sonKonum, boyut));
		sprite.setOrigin(sf::Vector2f(boyut.x / 2, boyut.y / 2));
		sprite.setScale(sf::Vector2f(3.0f, 3.0f));
		m_spriteListesi.push_back(sprite);
		sonKonum.x += boyut.x + 2;
	}
}

void Animasyon::animKursorOlustur(TexturePtr kaplama, const sf::Vector2i& konum, const sf::Vector2i& boyut, int cerceveSayisi)
{
	sf::Vector2i sonKonum = konum;
	for (int i = 0; i < cerceveSayisi; i++)
	{
		sf::Sprite sprite;

		sprite.setTexture(*kaplama);
		sprite.setTextureRect(sf::IntRect(sonKonum, boyut));
		sprite.setOrigin(sf::Vector2f(boyut.x / 2, boyut.y / 2));
		sprite.setScale(sf::Vector2f(-3.0f, -3.0f));
		sprite.setRotation(sf::degrees(180.f));
		m_spriteListesi.push_back(sprite);
		sonKonum.x += boyut.x + 2;
	}
}

void Animasyon::ciz(Pencere& pencere)
{
	m_spriteListesi[m_aktifSprite].setPosition(m_konum);
	pencere.ciz(m_spriteListesi[m_aktifSprite]);
}
