use chrono::Utc;
use sqlx::PgPool;
use crate::domain::models::{IssRecord, IssDataInput};

pub struct IssRepository;

impl IssRepository {
    pub async fn save(pool: &PgPool, data: IssDataInput) -> Result<IssRecord, sqlx::Error> {
        sqlx::query_as!(
            IssRecord,
            r#"
            INSERT INTO iss_data (latitude, longitude, visibility, fetched_at)
            VALUES ($1, $2, $3, $4)
            RETURNING id, latitude, longitude, visibility, fetched_at
            "#,
            data.latitude,
            data.longitude,
            data.visibility,
            Utc::now()
        )
        .fetch_one(pool)
        .await
    }

    pub async fn latest(pool: &PgPool, limit: i64) -> Result<Vec<IssRecord>, sqlx::Error> {
        sqlx::query_as!(
            IssRecord,
            r#"
            SELECT id, latitude, longitude, visibility, fetched_at
            FROM iss_data
            ORDER BY fetched_at DESC
            LIMIT $1
            "#,
            limit
        )
        .fetch_all(pool)
        .await
    }
}
