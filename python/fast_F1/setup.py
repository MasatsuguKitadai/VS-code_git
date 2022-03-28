import fastf1

fastf1.Cache.enable_cache('/home/masatsugu/git/code/python/fast_F1/cache')  
session = fastf1.get_session(2019, 'Monza', 'Q')
session.load(telemetry=False, laps=False, weather=False)
vettel = session.get_driver('VET')
print(f"Pronto {vettel['FirstName']}?")