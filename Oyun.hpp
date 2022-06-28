#pragma once
#include "TemelTurler.hpp"
#include "Pencere.hpp"
#include "AracPaneli.hpp"
#include "Top.hpp"
#include "Toplar.hpp"
#include "Cark.hpp"
#include "AnimKursor.hpp"
#include "Pet.hpp"
#include <vector>

class Oyun
{
public:
	Oyun();
	~Oyun();
	void setFps(int fps);
	void oyunuBaslat(unsigned int genislik = 600, unsigned int yukseklik = 800);
	void cizimFonksiyonu();
	TexturePtr kaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu = true);
	void oyunuAyarla();
	void arayuzleriYukle();
	void olaylariBagla();
	void fareHareket(int x, int y);
	void fareBasildi(sf::Event::MouseButtonEvent olay);
	void fareBirakma(sf::Event::MouseButtonEvent olay);
	void klavyeBasildi(sf::Keyboard::Key tus);
	void klavyeBirakma(sf::Keyboard::Key tus);
	void animasyonlariGuncelle(float sure);
	void oyunuKapat();


	void toplarEslesiyorMu(TopListesi);

	std::vector<float> m_konumXTek;
	std::vector<float> m_konumXCift;
	std::vector<float> m_konumY;

private:
	void saatiYenidenBaslat();

	sf::Time			m_gecenSure;
	sf::Time			m_cerceveSuresi;

	sf::Clock			m_saat;
	Pencere				m_pencere;
	KaplamaHaritasi		m_aracKaplamaListesi;
	int					m_fps;
	AracPaneliListesi	m_panelListesi;
	FontPtr				m_font;
	int					m_genislik;
	int					m_yukseklik;
	int					m_firlatmaKontrol;
	float				m_aci;
	bool				m_devamEdiyormu;
	bool				m_topFirlatildimi;
	bool				m_klavyeKitle;

	int					m_blokSayaci;
	int					m_ustSinirSayac;
	float				m_ustSinir;
	ToplarPtr			m_toplar;
	PetPtr				m_pet;
	CarkPtr				m_cark;
	AnimKursorPtr		m_animKursor;

};
