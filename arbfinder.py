import requests

API_KEY = '18f1d4cec6271ebe3df40ade3866942c'  # Replace with your actual API key
SPORT = 'soccer_epl'             # Example sport key (English Premier League)
REGIONS = 'uk,us,eu'             # Regions to include
MARKETS = 'h2h'                  # Betting markets (head-to-head)
ODDS_FORMAT = 'decimal'          # Odds format
DATE_FORMAT = 'iso'              # Date format

odds_url = f'https://api.the-odds-api.com/v4/sports/{SPORT}/odds/'

params = {
    'api_key': API_KEY,
    'regions': REGIONS,
    'markets': MARKETS,
    'oddsFormat': ODDS_FORMAT,
    'dateFormat': DATE_FORMAT,
}

response = requests.get(odds_url, params=params)

if response.status_code != 200:
    print(f"Failed to get odds: {response.status_code}, {response.text}")
    exit()

odds_json = response.json()

# Open bets.txt for writing
with open('bets.txt', 'w') as file:
    for game in odds_json:
        home_team = game['home_team']
        away_team = game['away_team']
        bookmakers = game['bookmakers']
        highest_odds = {'home': 0, 'away': 0, 'draw': 0}
        best_bookmakers = {'home': '', 'away': '', 'draw': ''}

        for bookmaker in bookmakers:
            bookmaker_name = bookmaker['title']  # Get the bookmaker's name
            for market in bookmaker['markets']:
                if market['key'] == 'h2h':
                    outcomes = market['outcomes']
                    for outcome in outcomes:
                        team = outcome['name']
                        odd = outcome['price']
                        if team == home_team:
                            if odd > highest_odds['home']:
                                highest_odds['home'] = odd
                                best_bookmakers['home'] = bookmaker_name
                        elif team == away_team:
                            if odd > highest_odds['away']:
                                highest_odds['away'] = odd
                                best_bookmakers['away'] = bookmaker_name
                        elif team.lower() == 'draw':
                            if odd > highest_odds['draw']:
                                highest_odds['draw'] = odd
                                best_bookmakers['draw'] = bookmaker_name

        # Check if draw odds are available
        if highest_odds['draw'] == 0:
            continue  # Skip matches without draw odds

        # Write the event information, odds, and bookmakers to bets.txt
        # Format: home_team|away_team|home_odds|home_bookmaker|away_odds|away_bookmaker|draw_odds|draw_bookmaker
        file.write(f"{home_team}|{away_team}|{highest_odds['home']}|{best_bookmakers['home']}|{highest_odds['away']}|{best_bookmakers['away']}|{highest_odds['draw']}|{best_bookmakers['draw']}\n")

print("bets.txt has been created with event details, highest odds, and bookmakers.")




