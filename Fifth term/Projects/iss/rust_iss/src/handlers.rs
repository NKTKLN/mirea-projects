use axum::{extract::{State, Json}};
use validator::Validate;

use crate::{
    state::AppState,
    repository::IssRepository,
    domain::{
        api::ApiResponse,
        error::{ApiError, ApiResult},
        models::IssDataInput,
    },
};

pub async fn create_iss_record(
    State(state): State<AppState>,
    Json(payload): Json<IssDataInput>,
) -> ApiResult<crate::domain::models::IssRecord> {

    let trace_id = "manual".to_string();

    payload.validate()
        .map_err(|e| ApiError::new("VALIDATION_ERROR", e.to_string(), trace_id.clone()))?;

    let rec = IssRepository::save(&state.db, payload)
        .await
        .map_err(|e| ApiError::new("DB_ERROR", e.to_string(), trace_id.clone()))?;

    Ok(Json(ApiResponse::ok(rec)))
}

pub async fn get_iss_records(
    State(state): State<AppState>,
) -> ApiResult<Vec<crate::domain::models::IssRecord>> {

    let trace_id = "manual".to_string();

    let data = IssRepository::latest(&state.db, 10)
        .await
        .map_err(|e| ApiError::new("DB_ERROR", e.to_string(), trace_id.clone()))?;

    Ok(Json(ApiResponse::ok(data)))
}
