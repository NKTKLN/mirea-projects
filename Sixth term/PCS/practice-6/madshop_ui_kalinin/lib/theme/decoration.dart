import 'package:flutter/material.dart';
import 'package:madshop_ui_kalinin/theme/colors.dart';


InputDecoration inputDecoration(
    String hint, {
    Widget? prefix,
    Widget? suffix,
  }) {
    return InputDecoration(
      hintText: hint,
      hintStyle: const TextStyle(
        fontFamily: 'Poppins',
        fontWeight: FontWeight.w500,
        fontSize: 13.83,
        color: AppColors.textHint,
      ),
      filled: true,
      fillColor: AppColors.backgroundInput,
      contentPadding: const EdgeInsets.symmetric(
        horizontal: 19.76,
        vertical: 15.81,
      ),
      prefixIcon: prefix,
      suffixIcon: suffix,
      border: OutlineInputBorder(
        borderRadius: BorderRadius.circular(52.37),
        borderSide: BorderSide.none,
      ),
      enabledBorder: OutlineInputBorder(
        borderRadius: BorderRadius.circular(52.37),
        borderSide: BorderSide.none,
      ),
      focusedBorder: OutlineInputBorder(
        borderRadius: BorderRadius.circular(52.37),
        borderSide: BorderSide.none,
      ),
    );
  }