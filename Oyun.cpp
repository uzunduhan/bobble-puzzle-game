#include "Oyun.hpp"
#include <iostream>
#include "Kenar.hpp"
#include "Kursor.hpp"
#include <filesystem>
#include "Animasyon.hpp"
#include "AnimasyonPet.hpp"
#include "TopAnimasyonlari.hpp"


Kenar kenar;
Kursor kursor;
Animasyon anim;
AnimasyonPet animPet;
TopAnimasyonlari topAnim;

static float m_blokBoyutGenislik;
static float m_blokBoyutYukseklik;

Oyun::Oyun()
{
	m_fps = 60;
	m_cerceveSuresi = sf::seconds(1.0f / m_fps);
	m_devamEdiyormu = false;
	m_aci = 0.f;

	m_blokSayaci = 0;
	m_ustSinirSayac = 0;
	m_ustSinir = 70.f;

	m_blokBoyutGenislik = 0;
	m_blokBoyutYukseklik = 0;
	float temp = 100.f;

	for (int i = 0; i < 8; i++)
	{
		m_konumXTek.push_back(temp + (i * 60));
	}
	for (int i = 0; i < 7; i++)
	{
		m_konumXCift.push_back(temp + (i * 60));
	}
	for (int i = 0; i < 12; i++)
	{
		m_konumY.push_back(temp + (i * 60));
	}
}

Oyun::~Oyun()
{
}

void Oyun::setFps(int fps)
{
}
TexturePtr Oyun::kaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu)
{
	if (m_aracKaplamaListesi.count(dosyaIsmi) == 0)
	{
		TexturePtr yeniKaplama = std::make_shared<sf::Texture>();
		sf::String yol = "./resimler/" + dosyaIsmi;
		std::filesystem::path tamyol(yol);

		if (arkaPlanOlsunmu)
		{
			if (yeniKaplama->loadFromFile(tamyol))
			{
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
			}
		}
		else
		{
			sf::Image image;
			if (image.loadFromFile(tamyol))
			{
				auto maskeRengi = image.getPixel(1, 3218);
				image.createMaskFromColor(maskeRengi);
				yeniKaplama->loadFromImage(image);
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
				return yeniKaplama;
			}
		}
		return yeniKaplama;

	}
	else
	{
		return m_aracKaplamaListesi[dosyaIsmi];
	}
}
void Oyun::oyunuAyarla()
{
	kenar.ayarla(m_genislik, m_blokBoyutGenislik, m_blokBoyutYukseklik);
	kursor.ayarla(m_genislik);
	m_toplar = std::make_shared <Toplar>(30.0f, 100.f, 100.f, "Top", this);
	m_toplar->topEkle(310.f, 702.5f, "Top", this);

	kaplamaEkle("puzzle.png", false);
	m_pet = std::make_shared<Pet>("Pet", this);
	animPet.petOlustur(kaplamaEkle("puzzle.png", false), sf::Vector2i(1, 3218), sf::Vector2i(31, 15), 8);
	animPet.m_konum = sf::Vector2f(400.f, 739.0f);

	m_cark = std::make_shared<Cark>("Cark", this);
	anim.carkOlustur(kaplamaEkle("puzzle.png", false), sf::Vector2i(1, 1805), sf::Vector2i(63, 39), 1);
	anim.m_konum = sf::Vector2f(310.f, 702.5);

	m_animKursor = std::make_shared<AnimKursor>("Kursor", this);
	anim.animKursorOlustur(kaplamaEkle("puzzle.png", false), sf::Vector2i(1, 1545), sf::Vector2i(63, 63), 1);
	anim.m_konum = sf::Vector2f(310.f, 702.5);

	arayuzleriYukle();
	olaylariBagla();
}
void Oyun::arayuzleriYukle()
{
	m_font = std::make_shared<sf::Font>();
	if (!m_font->loadFromFile("./fontlar/alev.ttf"))
	{
		std::cout << "font bulunamadi" << std::endl;
	}
	kaplamaEkle("Button.png");
	kaplamaEkle("Windows.png");
	AracPaneliPtr yeniPanel = std::make_shared<AracPaneli>();
	yeniPanel->fontAta(m_font);
	yeniPanel->aracKaplamasi(m_aracKaplamaListesi["Button.png"]);
	yeniPanel->arkaPlanAta(m_aracKaplamaListesi["Windows.png"], sf::IntRect(sf::Vector2i(799, 933), sf::Vector2i(550, 742)));


	auto btnYeniOyun = yeniPanel->butonEkle("Yeni Oyun");
	auto btnListe = yeniPanel->butonEkle("Liste");
	auto btnCikis = yeniPanel->butonEkle("Cikis");

	btnCikis->tiklaFonksiyonuEkle([&] {
		this->oyunuKapat();
	});

	btnYeniOyun->tiklaFonksiyonuEkle([&] {
		m_panelListesi[0]->gorunurluk(false);
		m_devamEdiyormu = true;
	});

	float x = (m_genislik - yeniPanel->boyutGetir().x) / 2;
	float y = (m_yukseklik - yeniPanel->boyutGetir().y) / 2;
	yeniPanel->konumAta(sf::Vector2f(x, y));

	m_panelListesi.push_back(yeniPanel);
}
void Oyun::olaylariBagla()
{
	m_pencere.hareketFonksiyonuEkle(
		std::bind(&Oyun::fareHareket, this, std::placeholders::_1, std::placeholders::_2));

	m_pencere.fareBasilmaFonksiyonuEkle(
		std::bind(&Oyun::fareBasildi, this, std::placeholders::_1));

	m_pencere.fareBirakilmaFonksiyonuEkle(
		std::bind(&Oyun::fareBirakma, this, std::placeholders::_1));
	m_pencere.tusBasilmaFonksiyonuEkle(
		std::bind(&Oyun::klavyeBasildi, this, std::placeholders::_1));

	m_pencere.tusBirakmaFonksiyonuEkle(
		std::bind(&Oyun::klavyeBirakma, this, std::placeholders::_1));

}
void Oyun::fareHareket(int x, int y)
{
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareHareket(x, y);
	}
}
void Oyun::fareBasildi(sf::Event::MouseButtonEvent olay)
{

	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareButonBasildi(olay);
	}
}
void Oyun::fareBirakma(sf::Event::MouseButtonEvent olay)
{
	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
	{

		siradaki->fareButonBirakildi(olay);

	}
}
void Oyun::klavyeBasildi(sf::Keyboard::Key tus)
{
	m_pet->tusBasildi(tus);

	if (tus == sf::Keyboard::Left)
		kursor.yonDegistir(YON::YON_SOL);

	if (tus == sf::Keyboard::Right)
		kursor.yonDegistir(YON::YON_SAG);

	if (tus == sf::Keyboard::Space)
	{
		m_topFirlatildimi = true;


	}
}

void Oyun::klavyeBirakma(sf::Keyboard::Key tus)
{
	m_pet->tusBirakma(tus);
}

void::Oyun::animasyonlariGuncelle(float sure)
{
	animPet.petGuncelle();
	m_pet->guncelle(sure * 20);
}

void Oyun::oyunuKapat()
{
	m_pencere.kapat();
}

void Oyun::oyunuBaslat(unsigned int genislik, unsigned int yukseklik)
{
	m_genislik = genislik;
	m_yukseklik = yukseklik;
	m_pencere.olustur(genislik, yukseklik, "SFML");

	oyunuAyarla();

	saatiYenidenBaslat();
	while (m_pencere.acikmi())
	{
		m_pencere.olayKontrol();

		if (m_saat.getElapsedTime() >= m_cerceveSuresi)
		{
			animasyonlariGuncelle(m_cerceveSuresi.asSeconds());
			cizimFonksiyonu();
			saatiYenidenBaslat();
		}
		else
		{
			sf::sleep(m_cerceveSuresi - m_saat.getElapsedTime());
		}

	}
}


void Oyun::toplarEslesiyorMu(TopListesi a)
{

	std::cout << a[0]->m_konum.x;

}

void Oyun::saatiYenidenBaslat()
{
	m_saat.restart();
}

void Oyun::cizimFonksiyonu()
{
	m_pencere.cizimeBasla();

	for (auto siradaki : m_panelListesi)
	{
		siradaki->ciz(m_pencere);
	}

	if (m_devamEdiyormu)
	{
		m_cark->ciz(m_pencere);
		m_pet->ciz(m_pencere);

		kursor.hareket();
		kursor.ciz(m_pencere);

		kenar.ciz(m_pencere);

		if (m_topFirlatildimi)
		{

			m_firlatmaKontrol++;

			if (m_firlatmaKontrol == 1)
			{
				m_aci = kursor.m_kursor.getRotation().asDegrees();
			}

			if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x >= 522.f || m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x <= 98.f)
			{
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizX = -1 * m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizX;
			}



			if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y <= m_ustSinir + m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_boyut)
			{
				float tempYerlesmeX = m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x - 62.5;

				int bolumX = tempYerlesmeX / 60;


				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizX = 0;
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizY = 0;

				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = m_konumY[m_ustSinirSayac];
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = m_konumXTek[bolumX];
			

				for (int i = 0; i < m_toplar->m_topDizisi.size() - 1; i++)
				{
					if (m_toplar->m_topDizisi[i]->m_konum.y == m_konumY[m_ustSinirSayac] && m_toplar->m_topDizisi[i]->m_konum.x == m_konumXTek[bolumX])
					{
						m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = m_konumXTek[bolumX - 1];
					}
				}


					m_toplar->topEkle(310.f, 702.5, "Top", this);
					m_blokSayaci++;
					m_firlatmaKontrol = 0;
					m_topFirlatildimi = false;
				}

				for (int i = 0; i < m_toplar->m_topDizisi.size() - 1; i++)
				{
					float mesafe = sqrt(pow(((m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x) - (m_toplar->m_topDizisi[i]->m_konum.x)), 2) +
						pow(((m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y) - (m_toplar->m_topDizisi[i]->m_konum.y)), 2));
					if (mesafe <= 50)
					{
						float tempYerlesmeX = m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x - 62.5;
						float tempYerlesmeY = m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y - 62.5;

						int bolumX = tempYerlesmeX / 50;
						int bolumY = tempYerlesmeY / 50;

						m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizX = 0;
						m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_hizY = 0;


						if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_sekil.getFillColor().toInteger() == m_toplar->m_topDizisi[i]->m_sekil.getFillColor().toInteger())
						{

							for (int j = 0; j < m_toplar->m_topDizisi.size() - 1; j++)
							{
								if (m_toplar->m_topDizisi[i]->m_sekil.getFillColor().toInteger() == m_toplar->m_topDizisi[j]->m_sekil.getFillColor().toInteger() && j != i && sqrt(pow(((m_toplar->m_topDizisi[j]->m_konum.x) - (m_toplar->m_topDizisi[i]->m_konum.x)), 2) +
									pow(((m_toplar->m_topDizisi[j]->m_konum.y) - (m_toplar->m_topDizisi[i]->m_konum.y)), 2)) <= 70)
								{

									m_toplar->m_topDizisi[i]->m_konum.x = -40;
									m_toplar->m_topDizisi[i]->m_konum.y = -40;
									m_toplar->m_topDizisi[i]->m_sekil.setFillColor(sf::Color::Transparent);
									m_toplar->m_topDizisi[i]->m_sekil.setRadius(1.f);

									m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = -40;
									m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = -40;
									m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_sekil.setFillColor(sf::Color::Transparent);
									m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_sekil.setRadius(1.f);


									m_toplar->m_topDizisi[j]->m_konum.x = -40;
									m_toplar->m_topDizisi[j]->m_konum.y = -40;
									m_toplar->m_topDizisi[j]->m_sekil.setFillColor(sf::Color::Transparent);
									m_toplar->m_topDizisi[j]->m_sekil.setRadius(1.f);

								}

							}

						}



						if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y >= m_toplar->m_topDizisi[i]->m_konum.y + 5)
						{

							if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x >= m_toplar->m_topDizisi[i]->m_konum.x)
							{
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = 30 + m_toplar->m_topDizisi[i]->m_konum.x;
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = 52.5 + m_toplar->m_topDizisi[i]->m_konum.y;
							}

							else if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x <= m_toplar->m_topDizisi[i]->m_konum.x)
							{
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = m_toplar->m_topDizisi[i]->m_konum.x - 30;
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = 52.5 + m_toplar->m_topDizisi[i]->m_konum.y;
							}
						}

						else if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y <= m_toplar->m_topDizisi[i]->m_konum.y)
						{
							if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x >= m_toplar->m_topDizisi[i]->m_konum.x)
							{
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = 30 + m_toplar->m_topDizisi[i]->m_konum.x;
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = m_toplar->m_topDizisi[i]->m_konum.y;
							}

							else if (m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x <= m_toplar->m_topDizisi[i]->m_konum.x)
							{
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = m_toplar->m_topDizisi[i]->m_konum.x - 30;
								m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = m_toplar->m_topDizisi[i]->m_konum.y;
							}
						}





						m_toplar->topEkle(310.f, 702.5, "Top", this);
						m_blokSayaci++;
						m_firlatmaKontrol = 0;
						m_topFirlatildimi = false;

					}

				}
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->firlatma(m_aci);
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->ciz(m_pencere);




			}
			else
			{
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.x = 310.f;
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->m_konum.y = 702.5f;
				m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1]->ciz(m_pencere);
			}

			if (m_blokSayaci == 5)
			{
				m_blokBoyutGenislik = 483.f;
				m_blokBoyutYukseklik += 60.f;
				for (auto siradaki : m_toplar->m_topDizisi)
				{
					if (siradaki != m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1])
					{
						if (siradaki->m_sekil.getFillColor() != sf::Color::Transparent)
							siradaki->m_konum.y += 60;
					}
				}
				m_ustSinirSayac++;
				m_ustSinir += 60;
				m_blokSayaci = 0;
				kenar.ayarla(m_genislik, m_blokBoyutGenislik, m_blokBoyutYukseklik);
			}


		
			m_toplar->ciz(m_pencere);

			m_animKursor->animKursorHareket();
			m_animKursor->ciz(m_pencere);

			for (auto siradaki : m_toplar->m_topDizisi)
			{
				if (siradaki->m_konum.y + 25 >= 635)
				{
					if (siradaki != m_toplar->m_topDizisi[m_toplar->m_topDizisi.size() - 1])
					{
						m_devamEdiyormu = false;
						m_pencere.kapat();
					}
				}
			}
		}
		m_pencere.cizimiBitir();
	}



