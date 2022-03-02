insert into products (name,description, price, weight) values ('mouse','Mouse dxpl-21', 6819.17, 94.4) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('monitor','LCD Monitor', 6469.63, 2.86) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('laptop-1','Laptop 3G', 5456.36, 33.59) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('printer-1','Printer HP', 4513.59, 64.04) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('desktop-1','Desktop pc', 5638.55, 74.6) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('battery-1','Power batery', 9722.98, 33.92) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('modem-1','Modem HP', 7171.35, 49.73) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('access-point-1','Access point', 4682.84, 27.4) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('tv-1','TV - 42', 5962.58, 30.12) ON CONFLICT (sku) DO NOTHING;
insert into products (name,description, price, weight) values ('smart-tv','Smart tv', 5987.86, 67.6) ON CONFLICT (sku) DO NOTHING;




INSERT INTO country (country_id, nicename, country_name,zipcode) VALUES
(1, 'AF',  'Afghanistan', 4),
(2, 'AL',  'Albania', 8),
(3, 'DZ',  'Algeria', 12),
(4, 'AS',  'American Samoa', 16),
(5, 'AD',  'Andorra', 20),
(6, 'AO',  'Angola', 24),
(7, 'AI',  'Anguilla',660),
(8, 'AQ',  'Antarctica',12),
(9, 'AG',  'Antigua and Barbuda', 28),
(10, 'AR', 'Argentina', 32 ),
(11, 'AM', 'Armenia', 51),
(12, 'AW', 'Aruba', 533),
(13, 'AU', 'Australia',  36),
(14, 'AT', 'Austria',  40),
(15, 'AZ', 'Azerbaijan',  31),
(16, 'BS', 'Bahamas', 44),
(17, 'BH', 'Bahrain', 48),
(18, 'BD', 'Bangladesh', 50),
(19, 'BB', 'Barbados',52),
(20, 'BY', 'Belarus', 112),
(21, 'BE', 'Belgium', 56),
(22, 'BZ', 'Belize', 84),
(23, 'BJ', 'Benin',  204),
(24, 'BM', 'Bermuda', 60),
(25, 'BT', 'Bhutan', 64),
(26, 'BO', 'Bolivia', 68),
(27, 'BA', 'Bosnia and Herzegovina',70),
(28, 'BW', 'Botswana', 72),
(30, 'BR', 'Brazil', 76);


insert into customer (name, phone, email,password) values ('Thaddeus', '11223344', 'tclayborn0@facebook.com'  , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Marnie',   '22334455', 'mbanasik1@army.mil'       , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Modesta',  '33445566', 'mmcgeffen2@amazon.com'    , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Thomasin', '44556677', 'tkynastone3@hostgator.com', '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Amity',    '55667788', 'asancho4@ow.ly'           , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Emeline',  '66778899', 'ecamillo5@mac.com'        , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Wynny',    '00112233', 'wbrood6@reference.com'    , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Gustavo',  '12345678', 'gustavo@ow.ly'            , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Nicolas',  '23456789', 'nicolas@mac.com'          , '81dc9bdb52d04dc20036dbd8313ed055');
insert into customer (name, phone, email,password) values ('Orlando',  '34567890', 'orlando6@reference.com'   , '81dc9bdb52d04dc20036dbd8313ed055');



insert into address (city, state, fk_country_id, street_number, address_type) values ('Armenia','Quindio', 1, 'street Hilton','billing' );
insert into address (city, state, fk_country_id, street_number, address_type) values ('Pereira','Risaralda', 2,  'Alcazar Court','billing');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Bogota','Cundinamarca',3, 'Halloy Lane','billing');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Medellin', 'Antioquia', 4, 'Grapeland Street','billing');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Atlantico', 'Barranquilla', 5, 'Great Falls Drive','billing');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Florencia','Caqueta', 6, 'Jameson Loop','shipping');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Quibdo','Choco',7,  'Kilcrease Loop','shipping');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Monteria','Cordoba',8, 'Mariposa Way','shipping');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Neiva', 'Huila',9, 'Oak Grove Lane','shipping');
insert into address (city, state, fk_country_id, street_number, address_type) values ('Villavicencio','Meta',10, 'Red Fox Loop','shipping');



