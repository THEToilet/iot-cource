= APIを使おう！

== Weather APIを使う

ResponeseCode
    200
//list[ResponesHeader][ResponesHeader]{
{
    "Transfer-Encoding": "chunked",
    "Connection": "keep-alive",
    "Vary": "Accept-Encoding",
    "CDN-PullZone": "93447",
    "CDN-Uid": "8fa3a04a-75d9-4707-8056-b7b33c8ac7fe",
    "CDN-RequestCountryCode": "FI",
    "CDN-EdgeStorageId": "615",
    "CDN-CachedAt": "2021-07-12 14:05:36",
    "CDN-RequestPullSuccess": "True",
    "CDN-RequestPullCode": "200",
    "CDN-RequestId": "a45be49d32c7a76559a3f3920d337f53",
    "CDN-Cache": "MISS",
    "Cache-Control": "public, max-age=180",
    "Content-Type": "application/json",
    "Date": "Mon, 12 Jul 2021 12:05:36 GMT",
    "Server": "BunnyCDN-FI1-615"
}
//}

//list[ResponseBody][ResponseBody]{
{
      "location": {
          "name": "Saitama",
          "region": "Saitama",
          "country": "Japan",
          "lat": 35.91,
          "lon": 139.66,
          "tz_id": "Asia/Tokyo",
          "localtime_epoch": 1626091536,
          "localtime": "2021-07-12 21:05"
      },
      "current": {
          "last_updated_epoch": 1626087600,
          "last_updated": "2021-07-12 20:00",
          "temp_c": 29.4,
          "temp_f": 84.9,
          "is_day": 0,
          "condition": {
              "text": "Partly cloudy",
              "icon": "//cdn.weatherapi.com/weather/64x64/night/116.png",
              "code": 1003
          },
          "wind_mph": 7.6,
          "wind_kph": 12.2,
          "wind_degree": 162,
          "wind_dir": "SSE",
          "pressure_mb": 1010.0,
          "pressure_in": 30.3,
          "precip_mm": 0.0,
          "precip_in": 0.0,
          "humidity": 61,
          "cloud": 47,
          "feelslike_c": 32.1,
          "feelslike_f": 89.8,
          "vis_km": 10.0,
          "vis_miles": 6.0,
          "uv": 7.0,
          "gust_mph": 9.2,
          "gust_kph": 14.8
    }
}
//}

=== APIとは？

=== サーバクライアント

=== WebサーバからのLチカ