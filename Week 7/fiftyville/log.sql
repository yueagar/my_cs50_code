-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query the description of the crime scene report about the theft
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- time: 10:15 am

-- Query the interview transcripts
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- Ruth: Thief got into a car in the bakery parking lot and drove away within 10 minutes ---> check security footage and look for the cars that left the parking lot in that time frame
-- Eugene: Thief withdrawed some money from the ATM on Leggett Street earlier in the morning
-- Raymond: Thief called someone who talked to them for less than a minute when leaving the bakery. Thief said that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket

-- Check security footage
SELECT hour,minute,license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit';
-- 10:16 5P2BI95
-- 10:18 94KL13X
-- 10:18 6P58WS2
-- 10:19 4328GD8
-- 10:20 G412CB7
-- 10:21 L93JTIZ
-- 10:23 322W7JE
-- 10:23 0NTHK55

-- Check ATM transactions
SELECT account_number,amount FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Check phone calls
SELECT caller,receiver,duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- Check flights
SELECT id,hour,minute,origin_airport_id,destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
-- Earliest flight: #36 8:20 am from ID: 8 to ID: 4

-- Get airport name from ID
SELECT full_name FROM airports WHERE id = 8
SELECT full_name FROM airports WHERE id = 4
SELECT city FROM airports WHERE id = 8
SELECT city FROM airports WHERE id = 4
-- 8->4: Fiftyville Regional Airport(Fiftyville)->LaGuardia Airport(New York City)

-- Check people information from license plate captured in security footage
SELECT name,phone_number,passport_number,license_plate FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit');
-- (499) 555-9472 sussy: 8294398571
-- (367) 555-5533 sussy: 5773159633
-- (770) 555-1861 sussy: 3592750733

-- Check passengers' passports
SELECT passport_number,name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- 5773159633 | Bruce
-- 8294398571 | Kelsey

-- Check the owners of bank accounts
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
-- Bruce

-- Note that Bruce called (375) 555-8161
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- Robin