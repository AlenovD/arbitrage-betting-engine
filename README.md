# Algorithmic Arbitrage Betting Engine 

A hybrid high-performance data pipeline designed to identify sports betting arbitrage opportunities in the Kazakhstan and Global markets.

## 🚀 Overview
This project implements a financial strategy known as *Arbitrage Betting*. It systematically scans multiple bookmakers to find market inefficiencies where the implied probabilities of all outcomes sum to less than 100%, guaranteeing a mathematical profit of 1-2% regardless of the match result.

The system is built with Python and C:
* **Python (`arbfinder.py`):** Handles API requests, JSON parsing, and data normalization.
* **C (`arbbetting.c`):** Handles filtering of large datasets due to the better time performance of C language.

## 🛠️ Tech Stack
* **Data Ingestion:** Python, Requests Library, The-Odds-API
* **Core Processing:** C (Standard Library)
* **Data Serialization:** Text document (`bets.txt`)

### Prerequisites
* Python 3.x
* GCC Compiler (MinGW for Windows or standard GCC for Linux/Mac)
* API Key from [The-Odds-API](https://the-odds-api.com/)
