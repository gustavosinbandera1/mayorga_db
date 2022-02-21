CREATE TABLE IF NOT EXISTS administrator (
    customer_id BIGSERIAL PRIMARY KEY,
    name  CHARACTER VARYING(50)  NOT NULL,
    email TEXT NOT NULL UNIQUE,
    phone CHARACTER VARYING(12) UNIQUE NOT NULL,
    password CHARACTER VARYING(50) NOT NULL
    );
CREATE TABLE IF NOT EXISTS customer (
    customer_id BIGSERIAL PRIMARY KEY,
    name  CHARACTER VARYING(50)  NOT NULL,
    email TEXT NOT NULL UNIQUE,
    phone CHARACTER VARYING(12) UNIQUE NOT NULL,
    password CHARACTER VARYING(50) NOT NULL
    );

CREATE TABLE IF NOT EXISTS address (
    address_id BIGSERIAL NOT NULL PRIMARY KEY,
    city VARCHAR(30) NOT NULL,
    state VARCHAR (30) NOT NULL,
    zip_code VARCHAR(5) NOT NULL,
    country VARCHAR(30) NOT NULL
    );

CREATE TABLE IF NOT EXISTS customer_address(
    fk_customer_id BIGINT NOT NULL,
    fk_address_id BIGINT NOT NULL,
    created_date_time DATE NOT NULL,
    CONSTRAINT customer_address_pk
        PRIMARY KEY (fk_customer_id, fk_address_id),
    CONSTRAINT customer_address_to_address_fk FOREIGN KEY (fk_address_id)
        REFERENCES address (address_id),
    CONSTRAINT customer_address_to_customer_fk FOREIGN KEY (fk_customer_id)
        REFERENCES customer (customer_id)
);


CREATE TABLE IF NOT EXISTS products (
    sku BIGSERIAL NOT NULL PRIMARY KEY,
    description CHARACTER VARYING(100),
    price NUMERIC(7,2),
    weight NUMERIC(7,2)
    );

CREATE TABLE IF NOT EXISTS orders (
    order_id BIGSERIAL NOT NULL PRIMARY KEY,
    fk_customer_id BIGINT NOT NULL,
    date DATE NOT NULL,
    payment_type CHARACTER VARYING(100) NOT NULL,
    CONSTRAINT order_to_customer_fk FOREIGN KEY(fk_customer_id)
      REFERENCES customer (customer_id)
    );


CREATE TABLE IF NOT EXISTS order_detail (
    num_detail BIGINT NOT NULL PRIMARY KEY,
    fk_order_id BIGINT NOT NULL,
    fk_product_sku BIGINT NOT NULL,
    quantity INTEGER NOT NULL,
    price NUMERIC(7,2) NOT NULL,
    CONSTRAINT detail_to_orders_fk FOREIGN KEY (fk_order_id)
        REFERENCES orders (order_id)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
   CONSTRAINT detail_to_products FOREIGN KEY (fk_product_sku)
        REFERENCES products (sku)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
    );

