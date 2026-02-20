import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:madshop_ui_kalinin/theme/colors.dart';
import 'package:madshop_ui_kalinin/theme/text_styles.dart';

class CartItemWidget extends StatelessWidget {
  final String image;
  final String name;
  final double price;
  final int quantity;
  final String description;
  final VoidCallback onIncreaseTap;
  final VoidCallback onDecreaseTap;
  final VoidCallback onRemoveTap;

  const CartItemWidget({
    super.key,
    required this.image,
    required this.name,
    required this.price,
    required this.quantity,
    required this.description,
    required this.onIncreaseTap,
    required this.onDecreaseTap,
    required this.onRemoveTap,
  });

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 109,
      child: Row(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            width: 129,
            height: 109,
            decoration: BoxDecoration(
              color: AppColors.white,
              borderRadius: BorderRadius.circular(9),
              boxShadow: [
                BoxShadow(
                  color: Colors.black.withValues(alpha: 0.102),
                  offset: const Offset(0, 5),
                  blurRadius: 10,
                ),
              ],
            ),
            child: Stack(
              children: [
                Center(
                  child: SizedBox(
                    width: 121.18,
                    height: 101.64,
                    child: ClipRRect(
                      borderRadius: BorderRadius.circular(5),
                      child: Image.asset(image, fit: BoxFit.cover),
                    ),
                  ),
                ),
                Positioned(
                  bottom: 10,
                  left: 10,
                  child: GestureDetector(
                    onTap: onRemoveTap,
                    child: Container(
                      width: 35,
                      height: 35,
                      decoration: BoxDecoration(
                        color: AppColors.white,
                        borderRadius: BorderRadius.circular(35),
                      ),
                      child: Center(
                        child: SvgPicture.asset(
                          'assets/icons/delete.svg',
                          width: 15,
                          height: 15,
                          colorFilter: ColorFilter.mode(
                            AppColors.deleteIcon,
                            BlendMode.srcIn,
                          ),
                        ),
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
          const SizedBox(width: 10),
          Expanded(
            child: Padding(
              padding: const EdgeInsets.symmetric(vertical: 4),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  SizedBox(
                    width: 196,
                    child: Text(
                      name,
                      style: AppTextStyles.productTitle,
                      maxLines: 2,
                      overflow: TextOverflow.ellipsis,
                    ),
                  ),
                  const SizedBox(height: 5),
                  Text(
                    description,
                    style: AppTextStyles.productDescription,
                    maxLines: 2,
                    overflow: TextOverflow.ellipsis,
                  ),

                  const Spacer(),

                  Padding(
                    padding: const EdgeInsets.only(bottom: 5),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Text(
                          '\$${price.toStringAsFixed(2)}',
                          style: AppTextStyles.productPriceInCart,
                        ),
                        Row(
                          children: [
                            GestureDetector(
                              onTap: onDecreaseTap,
                              child: SvgPicture.asset(
                                'assets/icons/less.svg',
                                width: 30,
                                height: 30,
                                colorFilter: ColorFilter.mode(
                                  AppColors.primary,
                                  BlendMode.srcIn,
                                ),
                              ),
                            ),
                            const SizedBox(width: 6),
                            Container(
                              width: 37,
                              height: 30,
                              alignment: Alignment.center,
                              decoration: BoxDecoration(
                                color: AppColors.bubbleBackground,
                                borderRadius: BorderRadius.circular(7),
                              ),
                              child: Text(
                                quantity.toString(),
                                style: AppTextStyles.productQuantity,
                              ),
                            ),
                            const SizedBox(width: 6),
                            GestureDetector(
                              onTap: onIncreaseTap,
                              child: SvgPicture.asset(
                                'assets/icons/more.svg',
                                width: 30,
                                height: 30,
                                colorFilter: ColorFilter.mode(
                                  AppColors.primary,
                                  BlendMode.srcIn,
                                ),
                              ),
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}
