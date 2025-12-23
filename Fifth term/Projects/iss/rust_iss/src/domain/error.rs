use axum::{Json, response::IntoResponse};
use crate::domain::api::ApiResponse;

#[derive(Debug)]
pub struct ApiError {
    pub code: &'static str,
    pub message: String,
    pub trace_id: String,
}

impl ApiError {
    pub fn new(code: &'static str, message: impl Into<String>, trace_id: String) -> Self {
        Self {
            code,
            message: message.into(),
            trace_id,
        }
    }
}

impl IntoResponse for ApiError {
    fn into_response(self) -> axum::response::Response {
        Json(ApiResponse::<()> ::err(
            self.code,
            self.message,
            self.trace_id,
        )).into_response()
    }
}

pub type ApiResult<T> = Result<Json<ApiResponse<T>>, ApiError>;
