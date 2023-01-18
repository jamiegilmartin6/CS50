-- Keep a log of any SQL queries you execute as you solve the mystery.
-- View the crime scene reports
SELECT * FROM crime_scene_reports;
--Theft occured at 10.15am at Humphrey Street bakery. 3 Interviews were conducted on the same day with witnesses.
--Find the interviews from the day
SELECT * FROM interviews WHERE month = 7 AND day = 28;
--Interview 1 (Ruth) within 10 mins of the theft the thief got into a car in the bakery parking lot and drove away
--Interview 2 (Eugene) recognized the thief, saw thief take out money from ATM on Leggett Street earlier that day
--Interview 3 (Raymond) thief called someone as they were leaving bakery. Planned to take earliest flight out tomorrow and asked the accomplice to purchase the tickets
--Look at the bakery security logs
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 15 AND 25;
SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 15 AND 25;
--1.) People who left the bakery car park when the thief did
--Check the atm records
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--Have the account numbers of possible thiefs
--Get names of people from possible thiefs accounts
SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--2.) Names of people who withdrew money from the Leggett atm the day of the crime
--Now try to put both lists of names together using INTERSECT
SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 15 AND 25 INTERSECT SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--FIND names of people who made a call as they left the bakery
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
--ALL phone calls made under a minute on the day of the theft
--Find names of all callers
SELECT people.name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
--3.) Names of all the people who made a call
--Now intersect all 3 lists
SELECT people.name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 INTERSECT SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 15 AND 25 INTERSECT SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--Left with Bruce and Diana (2 people)
--Now find if the person the thief rang booked a flight
SELECT * FROM flights WHERE month = 7 AND day = 29;
SELECT * FROM passengers JOIN flights ON passengers.flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29;
SELECT * FROM passengers JOIN flights ON passengers.flight_id = flights.id JOIN people ON people.passport_number = passengers.passport_number WHERE year = 2021 AND month = 7 AND day = 29;
SELECT * FROM airports;
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29;
--4.) People who were on the flights out of fiftyville same day as thief
--Intersect all 4 tables
SELECT people.name FROM people JOIN passengers ON people.passport_number = passengers.passport_number JOIN flights ON passengers.flight_id = flights.id WHERE year = 2021 AND month = 7 AND day = 29 INTERSECT SELECT people.name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 INTERSECT SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 15 AND 25 INTERSECT SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
--Checking what time each person took the flight at
--DIANA AND BRUCE were the culprits, DIANA flew at 16 BRUCE flew at 8.
SELECT * FROM flights JOIN passengers ON WHERE year = 2021 AND month = 7 AND day = 29;
SELECT people.name FROM passengers JOIN flights ON passengers.flight_id = flights.id JOIN people ON people.passport_number = passengers.passport_number WHERE year = 2021 AND month = 7 AND day = 29;
SELECT people.name, flights.hour FROM passengers JOIN flights ON passengers.flight_id = flights.id JOIN people ON people.passport_number = passengers.passport_number WHERE year = 2021 AND month = 7 AND day = 29;
--Previous query gets people who flew out and the hour they flew
SELECT * FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
SELECT destination_airport_id FROM passengers JOIN flights ON passengers.flight_id = flights.id JOIN people ON people.passport_number = passengers.passport_number WHERE year = 2021 AND month = 7 AND day = 29 AND name = 'Bruce';
--PRevious query gets destination aiport
SELECT * FROM airports WHERE id = 4;
--AIRPORT IS NEW YORK
SELECT phone_number FROM people WHERE name = 'Bruce';
SELECT receiver FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND name = 'Bruce';
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND name = 'Bruce');