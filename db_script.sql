create database music_store;

CREATE TABLE musician (
	id SERIAL PRIMARY KEY,
	name VARCHAR(120) NOT NULL,
	role_id INT NOT NULL,
	ensemble_id INT);

CREATE TABLE musician_roles (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL);

CREATE TABLE ensemble (
	id SERIAL PRIMARY KEY,
	name VARCHAR(60) NOT NULL,
	lider_id INT NOT NULL,
	type_id INT NOT NULL);

CREATE TABLE ensemble_types (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL);

CREATE TABLE instrument (
	id SERIAL PRIMARY KEY,
	name VARCHAR(60) NOT NULL);

CREATE TABLE musician_instr (
	musician_id INT NOT NULL,
	instrument_id INT NOT NULL);
	
CREATE TABLE composition (
	id SERIAL PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	text VARCHAR(1000) NOT NULL);

CREATE TABLE perfomance (
	id SERIAL PRIMARY KEY,
	composition_id INT NOT NULL,
	ensemble_id INT,
	musician_id INT,
	create_date DATE NOT NULL,
	_primary BOOLEAN NOT NULL,
	genre_id INT NOT NULL);

CREATE TABLE genre (
	id SERIAL PRIMARY KEY,
	name VARCHAR(60) NOT NULL);

CREATE TABLE disc (
	id SERIAL PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	creater_id INT NOT NULL,
	provider_id INT NOT NULL,
	create_date DATE NOT NULL,
	retail_price NUMERIC(10,2) NOT NULL,
	wholesale_price NUMERIC(10,2) NOT NULL,
	selled_past_year INT DEFAULT 0,
	selled_this_year INT DEFAULT 0,
	stock INT DEFAULT 0);

CREATE TABLE provider (
	id SERIAL PRIMARY KEY,
	name VARCHAR(120) NOT NULL,
	address VARCHAR(500) NOT NULL);

CREATE TABLE releaser (
	id SERIAL PRIMARY KEY,
	name VARCHAR(120) NOT NULL,
	address VARCHAR(500) NOT NULL);

CREATE TABLE perfomance_disc (
	perfomance_id INT NOT NULL,
	disc_id INT NOT NULL);

ALTER TABLE musician
	ADD FOREIGN KEY (role_id) REFERENCES musician_roles (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE musician
	ADD FOREIGN KEY (ensemble_id) REFERENCES ensemble (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE ensemble
	ADD FOREIGN KEY (lider_id) REFERENCES musician (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE ensemble
	ADD FOREIGN KEY (type_id) REFERENCES ensemble_types (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE musician_instr
	ADD FOREIGN KEY (musician_id) REFERENCES musician (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE musician_instr
	ADD FOREIGN KEY (instrument_id) REFERENCES instrument (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance
	ADD FOREIGN KEY (composition_id) REFERENCES composition (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance
	ADD FOREIGN KEY (ensembles_id) REFERENCES ensemble (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance
	ADD FOREIGN KEY (musician_id) REFERENCES musician (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance
	ADD FOREIGN KEY (genre_id) REFERENCES genre (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance_disc
	ADD FOREIGN KEY (perfomance_id) REFERENCES perfomance (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE perfomance_disc
	ADD FOREIGN KEY (disc_id) REFERENCES disc (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE disc
	ADD FOREIGN KEY (creater_id) REFERENCES releaser (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE disc
	ADD FOREIGN KEY (provider_id) REFERENCES provider (id)
	ON DELETE CASCADE ON UPDATE CASCADE;

INSERT INTO musician_roles (name) VALUES
	('Исполнитель'), ('Композитор'), ('Дирижёр'),
	('Руководитель ансамбля');

INSERT INTO musician (name, role_id) VALUES
	('Sandra', 1), ('Игорь Бурнышев', 1), ('Владимир Курдюков', 3),
	('Денис Ермолаев', 4);

INSERT INTO ensemble_types (name) VALUES
	('Классический оркестр'), ('Джазовая группа'), ('Квартет'),
	('Квинтет');

INSERT INTO ensemble (name, lider_id, type_id) VALUES
	('Burito', 4, 1);

INSERT INTO instrument (name) VALUES
	('Гитара'), ('Барабаны'), ('Скрипка'), ('Синтезатор');

INSERT INTO composition (name, text) VALUES
	('Little Girl', 'Venice night at 5 o’clock
	The station hazy light
	A sleepin` bum, a single girl
	She’s leavin` overnigt
	And she knows that it’s forever
	And she’ll never ever return
	In Italy on holidays
	She had to see da Vinci’s style
	All the arts for credit cards
	She would forgive him for a smile
	And she knows that it’s forever
	And she’ll never ever return
	Hey little girl
	Don’t wanna cause you pain
	But the big boys feel no sorrow
	Hey little girl
	They’re all the same
	But they feel no sorrow
	Tudododo doooh…
	There she is inside a train
	And now she’s leanin` back
	She’s got money for one day
	And nothing in the rack
	And she knows that it’s forever
	And she’ll never ever return
	Hey little girl
	Don’t wanna cause you pain
	But the big boys feel no sorrow
	Hey little girl
	They’re all the same
	But they feel no sorrow
	Tudododo doooh…');

INSERT INTO composition (name, text) VALUES
	('Когда звезды умрут', 'Вступление:
Ты не представляешь, как я далеко от тебя
(Далеко от тебя, далеко от тебя)
Здесь океан и тихо спят, полны тишины
(тишины полны, тишины полны)
Я с ними жду рассвет нового дня
(Новый день для меня, новый день для меня)
Я с ними вестей с новой земли
(Далеко , далеко )
Переход 1:
Когда звезды умрут над моей головой
Я не буду один, я буду с тобой
Когда больше дышать не сможет Земля
Я не буду один, есть ты у меня
Переход 2:
Когда звезды умрут над моей головой
Я не буду одна, я буду с тобой
Когда больше дышать не сможет Земля
Я не буду одна, есть ты у меня
Припев:
Ты не понимаешь, как мне нелегко без тебя
(Нелегко без тебя, нелегко без тебя)
Здесь мои песни не звучат, они не нужны
(Никому не нужны, никому не нужны)
Я так зову тебя тихо крича
(Я зову тебя, я зову тебя)
Я так зову, но ты где-то молчишь
(Далеко от тебя, далеко от тебя)
Переход 2:
Когда звезды умрут над моей головой
Я не буду одна, я буду с тобой
Когда больше дышать не сможет Земля
Я не буду одна, есть ты у меня');

INSERT INTO genre (name) VALUES
	('Металл'), ('Рок'), ('Блюз'), ('Хип-хоп');

INSERT INTO perfomance VALUES
	(1, 1, null, 1, '1986-01-15', true, 2),
	(2, 2, 1, null, '2019-04-01', true, 2);

INSERT INTO releaser (name, address) VALUES
	('EMI', 'USA, New York, Washington street, h.7, 49'),
	('RealMusic', 'UK, London, Green avenue, h.105');

INSERT INTO provider (name, address) VALUES
	('FirstOpt', 'Россия, г. Москва, бул. Университетский, д.14, стр. 2'),
	('Торговый_дом_музыки', 'Россия, Московская область, г. Балашиха,
	 	ул. Ромашек, д. 3');

INSERT INTO disc VALUES
	(1, 'Sandra The Best Hits', 1, 2, '2009-07-07', 1300, 1000, 250, 185, 300),
	(2, 'Burito Great Hits', 2, 2, '2019-04-01', 1200, 1000, 230, 190, 450);

INSERT INTO perfomance_disc VALUES
	(1, 1), (2, 2);

CREATE VIEW perfomance_view_ensemble AS
	SELECT perfomance.id, composition.name AS Произведение,
	ensemble.name AS Ансамбль, create_date AS Дата_выхода,
	CASE _primary WHEN true THEN 'Да' ELSE 'Нет' END AS Является_оригиналом,
	genre.name AS Жанр
	FROM perfomance INNER JOIN composition
	ON composition.id = composition_id
	INNER JOIN ensemble ON ensemble.id = ensembles_id
	INNER JOIN genre ON genre.id = genre_id;

CREATE VIEW perfomance_view_musician AS
	SELECT perfomance.id, composition.name AS Произведение,
	musician.name AS Исполнитель, create_date AS Дата_выхода,
	CASE _primary WHEN true THEN 'Да' ELSE 'Нет' END AS Является_оригиналом,
	genre.name AS Жанр
	FROM perfomance INNER JOIN composition
	ON composition.id = composition_id
	INNER JOIN musician ON musician.id = musician_id
	INNER JOIN genre ON genre.id = genre_id;