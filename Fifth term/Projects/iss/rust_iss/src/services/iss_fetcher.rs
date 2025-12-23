use std::{env, time::Duration};
use tokio::time::interval;
use reqwest::Client;
use tracing::{info, error};
use anyhow::Result;

use crate::{
    state::AppState,
    domain::{models::IssDataInput, nasa::NasaIssResponse},
    repository::IssRepository,
};

pub async fn run_iss_fetcher(state: AppState) {
    let every = env::var("FETCH_EVERY_SECONDS")
        .ok()
        .and_then(|v| v.parse::<u64>().ok())
        .unwrap_or(10);

    let api_url = env::var("NASA_API_URL")
        .expect("NASA_API_URL not set");

    let api_key = env::var("NASA_API_KEY")
        .expect("NASA_API_KEY not set");

    let client = Client::new();
    let mut ticker = interval(Duration::from_secs(every));

    info!("ISS fetcher started, interval = {}s", every);

    loop {
        ticker.tick().await;

        match fetch_and_save(&client, &api_url, &api_key, &state).await {
            Ok(_) => info!("ISS data fetched and saved"),
            Err(e) => error!("ISS fetch error: {}", e),
        }
    }
}

async fn fetch_and_save(
    client: &Client,
    url: &str,
    api_key: &str,
    state: &AppState,
) -> Result<()> {

    let resp = client
        .get(url)
        .send()
        .await?
        .json::<NasaIssResponse>()
        .await?;

    let input = IssDataInput {
        latitude: resp.latitude,
        longitude: resp.longitude,
        visibility: resp.visibility,
    };

    IssRepository::save(&state.db, input).await?;

    Ok(())
}
