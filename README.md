# SİSTEM PROGRAMLAMA DERSİ YAZ OKULU PROJESİ

## Uygulama 1 (30)

Hazırlayacak olduğunuz program çalıştırıldıktan sonra program sonlandırılıncaya kadar mouse ekran koordinatlarını okuyarak kullanıcı tarafından belirlenen dosyaya bilgilerin aktarımını yapmalıdır. Program koordinat bilgileri ile birlikte dosyaya timestamp bilgiside yazmalıdır.

Örnek çalıştırma : C:\user\unalc> ./mouse_event event_file

Örnek çıktı dosyası :

```
timestamp            x  y
04.08.2021 15:42:00 134 89
04.08.2021 15:42:03 45 178
```

## Uygulamala 2 (70)

Hazırlayacak olduğunuz encryption isimli program **libfdr kütüphanesini** kullanarak parametre olarak aldığı dosyada bulunan kelimeleri (karakter bazında), parametre olarak aldığı aralıkta üretilecek rasgele sayılar ile XOR operatörü kullanarak şifreleyecek ve yeni bir şifreli kelime elde edecektir. XOR ile şifrelenmiş dosyayı ilgili dizine kaydedecektir. Şifreleme işleminin tamamlanması için şifreli dosyadaki veriler libfdr dllist yapısı kullanılarak ters bir şekilde reverse_encrtpted_file isimli dosyaya yazdırılacaktır.

Örnek :

Okunan kelime(fields kullanılacak)-> sakarya

s-> 73 üretilen random sayı-> 56 şifreli karakter (xor operation)->113(q)

Örnek çalıştırma : 

C:\user\unalc> ./encrypt plaintext 0-200

Libfdr-dlllist kullanılarak şifreli dosya ters sırada → **reverse_encrtpted_file**
isimli dosyaya yazdırılacaktır.


### Nasıl Kurulur
encrypt klasörü altında:

```
make
```
Derleme sırasına bir hata alınmaz ise aynı klasörde **encrypt** adında bir dosya oluşur.


### Nasıl Çalıştrılır
encrypt klasörü altındaki **encrypt** adlı program  iki parametre ile çalıştırılır. ilk parametre dosya konumu, ikinci parametre minimum ile maksimum aralığı aralarında (-) olacak şekilde. 

Örnek:

```
./encrypt test.dat 3-200
```

Çalıştırma sonucunda ekran çıkışı örnekteki gibidir.

```
Crypting key is 145.
1: Engin -> �����
2: Akdeniz -> �������
3: Hello -> �����
4: World -> �����
5: Test -> ����
6: Data -> ����
```

ve XOR ile şifrelenmiş metin *reverse_encrtpted_file* dosyasına ters sırada yazılır.