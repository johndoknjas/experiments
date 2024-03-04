from multiprocessing.pool import ThreadPool
from typing import Optional
from datetime import datetime, timedelta
from time import sleep
import requests

sleep_till: Optional[datetime] = None
num_api_calls_made: int = 0
sleep_till: Optional[datetime] = None
def getJSON(api_key: str, typeOfRequest: str, uuid: str) -> dict:
    """ This function is used for getting a JSON from Hypixel's Public API. """
    global sleep_till
    global num_api_calls_made

    if sleep_till and (sleep_duration := (sleep_till - datetime.now()).total_seconds()) >= 0:
        print(f"Sleeping until {sleep_till.strftime('%I:%M:%S %p')} for rate limiting.")
        print(f"{num_api_calls_made} api calls made total since the program started.")
        sleep(sleep_duration)
    sleep_till = None

    num_api_calls_made += 1

    requestEnd = f"uuid={uuid}"
    requestURL = f"https://api.hypixel.net/{typeOfRequest}?{requestEnd}"
    response = requests.get(requestURL, headers={"API-Key": api_key})
    responseHeaders, responseJSON = response.headers, response.json()

    if 'RateLimit-Remaining' in responseHeaders:
        print(f"{responseHeaders['RateLimit-Remaining']} remaining allowed requests for current period.")
        if int(responseHeaders['RateLimit-Remaining']) <= 1:
            sleep_till = datetime.now() + timedelta(seconds=int(responseHeaders['RateLimit-Reset'])+1)

    if not responseJSON['success']:
        raise Exception(responseJSON)
    if typeOfRequest == 'player' and responseJSON['player'] is None:
        raise Exception(uuid)
    try:
        return responseJSON[typeOfRequest]
    except KeyError:
        return responseJSON

def worker(api_key):
    getJSON(api_key, 'status', uuid='f7c77d999f154a66a87dc4a51ef30d19')['session']['online']

def main():
    api_key = input("Enter your key: ")
    pool = ThreadPool(8)
    while True:
        pool.apply_async(worker, (api_key,))

if __name__ == '__main__':
    main()