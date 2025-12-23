mod config;
mod state;
mod domain;
mod handlers;
mod repository;
mod middleware;
mod services;

use axum::{Router, routing::{get, post}};
use tower_http::trace::TraceLayer;
use tokio::net::TcpListener;

#[tokio::main]
async fn main() {
    tracing_subscriber::fmt::init();

    let db = config::init_db().await;
    let redis = config::init_redis();

    let state = state::AppState { db, redis };
    let fetcher_state = state.clone();

    let app = Router::new()
        .route("/api/iss", post(handlers::create_iss_record))
        .route("/api/iss/latest", get(handlers::get_iss_records))
        .layer(axum::middleware::from_fn_with_state(
            state.clone(),
            middleware::rate_limit,
        ))
        .layer(TraceLayer::new_for_http())
        .with_state(state);

    tokio::spawn(async move {
        services::iss_fetcher::run_iss_fetcher(fetcher_state).await;
    });

    let listener = TcpListener::bind("0.0.0.0:3000").await.unwrap();
    axum::serve(listener, app).await.unwrap();
}
