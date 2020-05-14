Инсталация
------------

За да пуснете сървъра локално, трябва да инсталирате pipenv:

    $ sudo apt install pipenv

След това отидете до директорията в която се намира сървърът, инсталирайте всички необходими пакети и стартирайте средата:

    $ cd VMKS/Server

    $ pipenv install

    $ pipenv shell

Стартирайте сървъра с командата:

    $ python manage.py runserver 0:8000 // local

Чрез ардуино средата качете кода от папката Module/NodeMCU на esp модула и кода от Module/Arduion на Arduino контролера, като предварително промените двете полета ssid и password със съответните Ви име и парола на WiFi мрежата.

Създайте си super user в сървъра с командата:

    $ python manage.py createsuperuser

С този User се логнете в админския панел на сървъра, който се намира на http://localhost:8000/admin. В този панел можете да създавате нови профили, както и да променяте и изтривате стари. Можете също така и да задавате текущ профил, който се ползва от След като кодът се зареди на модулите, при засичане на движение ще се взимат настройките от сървъра и ще се пускат светлините.
 за настройка на светлината.


![](https://i.imgur.com/Dl321X1.png)

![](https://i.imgur.com/B0Abbci.png)

След като кодът се зареди на модулите, при засичане на движение ще се взимат настройките от сървъра и ще се пускат светлините.

