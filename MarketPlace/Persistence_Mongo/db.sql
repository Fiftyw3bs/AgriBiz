CREATE TABLE IF NOT EXISTS Login_Details (
    user_id SERIAL NOT NULL,
    username VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    unique (username),
    unique (user_id),
    last_login TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT NOW(),
    PRIMARY KEY(user_id, username)
);

CREATE TABLE IF NOT EXISTS Auth (
    user_id INT NOT NULL REFERENCES Login_Details(user_id) ON DELETE CASCADE,
    token_type VARCHAR(255) NOT NULL,
    expires_in INT NOT NULL,
    access_token VARCHAR(255) NOT NULL,
    refresh_token VARCHAR(255) NOT NULL,
    scope VARCHAR(255) NOT NULL,
    issuance_date TIMESTAMP NOT NULL DEFAULT NOW(),
    PRIMARY KEY(user_id)
);

CREATE TABLE IF NOT EXISTS Users (
    user_id SERIAL NOT NULL,
    username VARCHAR(255) NOT NULL,
    email VARCHAR(255),
    enabled BOOLEAN DEFAULT FALSE,
    last_login TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT NOW(),
    PRIMARY KEY(user_id)
);

CREATE TABLE IF NOT EXISTS ContactDetails (
    user_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    firstName VARCHAR(100),
    middleName VARCHAR(100),
    lastName VARCHAR(100),
    address VARCHAR(255),
    city VARCHAR(126),
    state VARCHAR(126),
    postalCode INT,
    phone INT,
    PRIMARY KEY(user_id)
);

INSERT INTO ContactDetails (user_id, phone) VALUES
    (1, 657564),
    (2, 2323423);

-- Wallet Table
CREATE TABLE IF NOT EXISTS Wallet (
    user_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    balance INT DEFAULT 0,
    PRIMARY KEY(user_id)
);

INSERT INTO Wallet (user_id, balance) VALUES
    (1, 2300),
    (2, 453);
-- 

-- CreditPoint Table
CREATE TABLE IF NOT EXISTS CreditPoint (
    user_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    totalPoints INT DEFAULT 0,
    cashedOutPoints INT DEFAULT 0,
    PRIMARY KEY(user_id)
);

INSERT INTO CreditPoint (user_id, totalPoints) VALUES
    (1, 21304),
    (2, 10000);
--

-- Post Table
CREATE TABLE IF NOT EXISTS Post (
    post_id SERIAL NOT NULL,
    title text,
    content text,
    postedOn TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT NOW(),
    user_id INT NOT NULL,
    PRIMARY KEY(post_id),
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

INSERT INTO Post (title, content, user_id) VALUES 
    ('First Post', 'Test', 1),
    ('First Post1', 'Test1', 1),
    ('First Post2', 'Test2', 2),
    ('First Post3', 'Test3', 2);
--

-- Inherits from Post
CREATE TABLE IF NOT EXISTS AbuseOfAuthority (
    nameOfOfficer VARCHAR(255),
    occurence_date TIMESTAMP WITH TIME ZONE NOT NULL,
    location_id INT NOT NULL,
    CONSTRAINT AbuseOfAuthority_pkey PRIMARY KEY (post_id)
) INHERITS (Post);

CREATE TABLE Countries (
    country_id SERIAL NOT NULL,
    country_name VARCHAR(255) NOT NULL,
    country_flag VARCHAR(255),
    PRIMARY KEY (country_name)
);

INSERT INTO Countries (country_name) VALUES
                      ("Nigeria");

CREATE TABLE States (
    state_id SERIAL NOT NULL,
    country_id VARCHAR(255) NOT NULL REFERENCES Countries(country_id) ON DELETE CASCADE,
    state_name VARCHAR(255) NOT NULL,
    PRIMARY KEY (state_id, country_id)
);

INSERT INTO States (country_id, state_name) VALUES
                   (1, "Lagos");

CREATE TABLE Cities (
    city_id SERIAL NOT NULL,
    state_id INT NOT NULL REFERENCES States(state_id) ON DELETE CASCADE,
    city_name VARCHAR(255) NOT NULL,
    PRIMARY KEY (city_id, state_id)
);

INSERT INTO Cities (state_id, city_name) VALUES
                   (1, "Oshodi");

CREATE TABLE Streets (
    street_id SERIAL NOT NULL,
    city_id VARCHAR(255) NOT NULL REFERENCES Cities(city_id) ON DELETE CASCADE,
    street_name text NOT NULL,
    PRIMARY KEY (street_id, city_id)
);

INSERT INTO Streets (city_id, street_name) VALUES
                    (1, "Arowojobe Street");

-- In the OOP declarations and definitions of classes that use Location, Location shall
-- be implemented as an inner class.
CREATE TABLE IF NOT EXISTS Locations (
    location_id SERIAL UNIQUE NOT NULL,
    country_id INT NOT NULL,
    state_id INT NOT NULL,
    city_id INT NOT NULL,
    street_id INT NOT NULL,
    cordinates varchar(30),
    PRIMARY KEY (location_id, country_id, state_id, city_id, street_id)
);

INSERT INTO Locations (country_id, state_id, city_id, street_id) VALUES
                      (1, 1, 1, 1);

CREATE TABLE IF NOT EXISTS User_Post_Rating (
    post_id INT NOT NULL REFERENCES Post (post_id) ON DELETE CASCADE,
    rater_id INT NOT NULL,
    vote INT NOT NULL CHECK(vote in (-1, +1)),
    PRIMARY KEY(rater_id, post_id)
);

INSERT INTO User_Post_Rating (post_id, rater_id, vote) VALUES 
    (1, 2, +1),
    (2, 1, +1),
    (3, 1, -1),
    (4, 2, -1);

CREATE TABLE IF NOT EXISTS Comment (
    comment_id SERIAL NOT NULL,
    content text,
    user_id int not null,
    post_id int not null,
    commentedOn TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT NOW(),
    PRIMARY KEY (comment_id),
    FOREIGN KEY (post_id) REFERENCES Post(post_id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
);

INSERT INTO Comment (content, user_id, post_id) VALUES 
    ('What have you got to say?', 1, 1),
    ('Nonsense?', 2, 1),
    ('Bullshit?', 1, 2),
    ('Sensible Enough?', 1, 2);

CREATE TABLE IF NOT EXISTS User_Comment_Rating (
    comment_id INT NOT NULL REFERENCES Comment (comment_id) ON DELETE CASCADE,
    rater_id INT NOT NULL,
    vote INT NOT NULL CHECK(vote in (-1, +1)),
    PRIMARY KEY(rater_id, comment_id)
);

INSERT INTO User_Comment_Rating (comment_id, rater_id, vote) VALUES 
    (1, 1, +1),
    (2, 2, +1),
    (3, 2, -1),
    (4, 2, -1);

CREATE TABLE IF NOT EXISTS Tag (
    tag_id SERIAL NOT NULL,
    descr VARCHAR(25) NOT NULL,
    PRIMARY KEY(tag_id)
);

INSERT INTO Tag (descr) VALUES 
    ('Corruption'),
    ('Stagnation'),
    ('Complication');

CREATE TABLE IF NOT EXISTS Post_Tag (
    post_id INT NOT NULL REFERENCES Post (post_id) ON DELETE CASCADE,
    tag_id INT NOT NULL REFERENCES Tag (tag_id),
    PRIMARY KEY(post_id, tag_id)
);

INSERT INTO Post_Tag (post_id, tag_id) VALUES
    (1,1),
    (1,2),
    (1,3);

CREATE OR REPLACE FUNCTION "reset_sequence" (tablename text) RETURNS "pg_catalog"."void" AS 
$body$  
  DECLARE 
  BEGIN 
  EXECUTE 'SELECT setval( ''' 
  || tablename  
  || '_id_seq'', ' 
  || '(SELECT id + 1 FROM "' 
  || tablename  
  || '" ORDER BY id DESC LIMIT 1), false)';  
  END;  
$body$  LANGUAGE 'plpgsql';


-- AgriBiz System

CREATE TYPE BidStatus AS ENUM (
    'PENDING',
    'ACCEPTED',
    'DECLINED',
    'SUSPENDED'
);

CREATE TABLE IF NOT EXISTS Bid (
    bid_id SERIAL NOT NULL,
    bidding_price FLOAT NOT NULL DEFAULT 0,
    quantity FLOAT NOT NULL DEFAULT 0,
    bidder_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    bid_status BidStatus NOT NULL DEFAULT 'PENDING',
    bid_date TIMESTAMP NOT NULL DEFAULT NOW(),
    PRIMARY KEY (bid_id)
);

CREATE TABLE IF NOT EXISTS FarmProduce (
    farm_produce_id SERIAL NOT NULL,
    name VARCHAR(255) NOT NULL,
    description TEXT NOT NULL,
    PRIMARY KEY (farm_produce_id)
);

CREATE TYPE OrderType AS ENUM (
    'BUY',
    'SELL'
);

CREATE TYPE OrderStatus AS ENUM (
    'ACCEPTED',
    'PENDING',
    'COMPLETED',
    'SUSPENDED',
    'UNKNOWN'
);

CREATE TABLE IF NOT EXISTS Orders (
    order_id SERIAL NOT NULL,
    orderer_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    cost_per_kg FLOAT NOT NULL DEFAULT 0,
    quantity FLOAT NOT NULL DEFAULT 0,
    location_id INT NOT NULL,
    harvest_date TIMESTAMP NOT NULL,
    date_posted TIMESTAMP NOT NULL DEFAULT NOW(),
    description TEXT NOT NULL,
    date_complete TIMESTAMP,
    order_type OrderType NOT NULL,
    order_status OrderStatus NOT NULL DEFAULT 'PENDING',
    PRIMARY KEY (order_id)
);

CREATE TABLE IF NOT EXISTS Bid_Order (
    bid_id INT NOT NULL REFERENCES Bid(bid_id) ON DELETE CASCADE,
    order_id INT NOT NULL REFERENCES Orders(order_id) ON DELETE CASCADE,
    PRIMARY KEY(bid_id, order_id)
);

CREATE TABLE IF NOT EXISTS Roles (
    role_id SERIAL NOT NULL,
    name VARCHAR(255) NOT NULL,
    PRIMARY KEY (role_id)
);

INSERT INTO Roles (name) VALUES ('Admin'), ('Seller'), ('Buyer');

CREATE TABLE IF NOT EXISTS User_Roles (
    user_id INT NOT NULL REFERENCES Users(user_id) ON DELETE CASCADE,
    role_id INT NOT NULL REFERENCES Roles(role_id) ON DELETE CASCADE,
    PRIMARY KEY (user_id, role_id)
);

INSERT INTO User_Roles (user_id, role_id) VALUES (1, 1), (1,2), (1,3);
