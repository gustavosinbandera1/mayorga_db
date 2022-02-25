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




INSERT INTO country (country_id, iso, country_name, nicename, iso3, zipcode, phonecode) VALUES
(1, 'AF', 'AFGHANISTAN', 'Afghanistan', 'AFG', 4, 93),
(2, 'AL', 'ALBANIA', 'Albania', 'ALB', 8, 355),
(3, 'DZ', 'ALGERIA', 'Algeria', 'DZA', 12, 213),
(4, 'AS', 'AMERICAN SAMOA', 'American Samoa', 'ASM', 16, 1684),
(5, 'AD', 'ANDORRA', 'Andorra', 'AND', 20, 376),
(6, 'AO', 'ANGOLA', 'Angola', 'AGO', 24, 244),
(7, 'AI', 'ANGUILLA', 'Anguilla', 'AIA', 660, 1264),
(8, 'AQ', 'ANTARCTICA', 'Antarctica', NULL, NULL, 0),
(9, 'AG', 'ANTIGUA AND BARBUDA', 'Antigua and Barbuda', 'ATG', 28, 1268),
(10, 'AR', 'ARGENTINA', 'Argentina', 'ARG', 32, 54),
(11, 'AM', 'ARMENIA', 'Armenia', 'ARM', 51, 374),
(12, 'AW', 'ARUBA', 'Aruba', 'ABW', 533, 297),
(13, 'AU', 'AUSTRALIA', 'Australia', 'AUS', 36, 61),
(14, 'AT', 'AUSTRIA', 'Austria', 'AUT', 40, 43),
(15, 'AZ', 'AZERBAIJAN', 'Azerbaijan', 'AZE', 31, 994),
(16, 'BS', 'BAHAMAS', 'Bahamas', 'BHS', 44, 1242),
(17, 'BH', 'BAHRAIN', 'Bahrain', 'BHR', 48, 973),
(18, 'BD', 'BANGLADESH', 'Bangladesh', 'BGD', 50, 880),
(19, 'BB', 'BARBADOS', 'Barbados', 'BRB', 52, 1246),
(20, 'BY', 'BELARUS', 'Belarus', 'BLR', 112, 375),
(21, 'BE', 'BELGIUM', 'Belgium', 'BEL', 56, 32),
(22, 'BZ', 'BELIZE', 'Belize', 'BLZ', 84, 501),
(23, 'BJ', 'BENIN', 'Benin', 'BEN', 204, 229),
(24, 'BM', 'BERMUDA', 'Bermuda', 'BMU', 60, 1441),
(25, 'BT', 'BHUTAN', 'Bhutan', 'BTN', 64, 975),
(26, 'BO', 'BOLIVIA', 'Bolivia', 'BOL', 68, 591),
(27, 'BA', 'BOSNIA AND HERZEGOVINA', 'Bosnia and Herzegovina', 'BIH', 70, 387),
(28, 'BW', 'BOTSWANA', 'Botswana', 'BWA', 72, 267),
(29, 'BV', 'BOUVET ISLAND', 'Bouvet Island', NULL, NULL, 0),
(30, 'BR', 'BRAZIL', 'Brazil', 'BRA', 76, 55);


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



insert into customer_address (fk_customer_id, fk_address_id,created_date_time) values (1, 1,current_timestamp);
insert into customer_address (fk_customer_id, fk_address_id,created_date_time) values (1, 26,current_timestamp);
insert into customer_address (fk_customer_id, fk_address_id,created_date_time) values (2, 2,current_timestamp);
insert into customer_address (fk_customer_id, fk_address_id,created_date_time) values (2, 8,current_timestamp);
