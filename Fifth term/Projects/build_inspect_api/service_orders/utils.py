from data import orders

def find_order_by_id(order_id: str):
    return next((o for o in orders if o["id"] == order_id), None)

def filter_orders_by_user(user_id: str):
    return [o for o in orders if o["user_id"] == user_id]
