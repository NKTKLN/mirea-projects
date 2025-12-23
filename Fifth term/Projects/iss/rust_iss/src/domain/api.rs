use serde::Serialize;

#[derive(Serialize)]
pub struct ApiResponse<T> {
    pub ok: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub data: Option<T>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub error: Option<ApiErrorBody>,
}

#[derive(Serialize)]
pub struct ApiErrorBody {
    pub code: String,
    pub message: String,
    pub trace_id: String,
}

impl<T> ApiResponse<T> {
    pub fn ok(data: T) -> Self {
        Self {
            ok: true,
            data: Some(data),
            error: None,
        }
    }

    pub fn err(code: &str, message: String, trace_id: String) -> Self {
        Self {
            ok: false,
            data: None,
            error: Some(ApiErrorBody {
                code: code.to_string(),
                message,
                trace_id,
            }),
        }
    }
}
