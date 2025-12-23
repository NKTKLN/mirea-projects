use chrono::{DateTime, Utc};
use serde::{Deserialize, Serialize};
use validator::Validate;

#[derive(Debug, Deserialize, Validate)]
pub struct IssDataInput {
    #[validate(range(min = -90.0, max = 90.0))]
    pub latitude: f64,

    #[validate(range(min = -180.0, max = 180.0))]
    pub longitude: f64,

    pub visibility: String,
}

#[derive(Debug, Serialize, sqlx::FromRow)]
pub struct IssRecord {
    pub id: i32,
    pub latitude: f64,
    pub longitude: f64,
    pub visibility: String,
    pub fetched_at: DateTime<Utc>,
}
