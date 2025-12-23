use axum::{extract::State, middleware::Next, http::Request};
use redis::AsyncCommands;
use crate::{state::AppState, domain::error::ApiError};
use uuid::Uuid;

pub async fn rate_limit(
    State(state): State<AppState>,
    mut req: Request<axum::body::Body>,
    next: Next,
) -> Result<axum::response::Response, ApiError> {

    let trace_id = Uuid::new_v4().to_string();
    req.extensions_mut().insert(trace_id.clone());

    let ip = req
        .headers()
        .get("x-forwarded-for")
        .and_then(|v| v.to_str().ok())
        .unwrap_or("unknown");

    let key = format!("rate_limit:{}", ip);
    let mut con = state.redis.get_multiplexed_async_connection().await
        .map_err(|_| ApiError::new("CACHE_ERROR", "redis unavailable", trace_id.clone()))?;

    let count: i32 = con.incr(&key, 1).await
        .map_err(|_| ApiError::new("CACHE_ERROR", "redis incr failed", trace_id.clone()))?;

    if count == 1 {
        let _: () = con.expire(&key, 60).await.unwrap();
    }

    if count > 100 {
        return Err(ApiError::new(
            "RATE_LIMITED",
            "too many requests",
            trace_id,
        ));
    }

    Ok(next.run(req).await)
}
