use std::env;
use sqlx::{PgPool, postgres::PgPoolOptions};

pub async fn init_db() -> PgPool {
    let url = env::var("DATABASE_URL")
        .unwrap_or_else(|_| "postgres://postgres:password@localhost:5432/iss_data".into());

    PgPoolOptions::new()
        .max_connections(10)
        .connect(&url)
        .await
        .expect("Postgres connection failed")
}

pub fn init_redis() -> redis::Client {
    let url = env::var("REDIS_URL")
        .unwrap_or_else(|_| "redis://127.0.0.1:6379".into());

    redis::Client::open(url).expect("Redis connection failed")
}
