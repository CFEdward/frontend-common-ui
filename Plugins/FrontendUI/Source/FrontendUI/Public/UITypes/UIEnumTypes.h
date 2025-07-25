﻿// Eduard Ciofu All Rights Reserved

#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
	OK,
	YesNo,
	OKCancel	UMETA(DisplayName = "OK Cancel"),
	Unknown		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType : uint8
{
	Confirmed,
	Cancelled,
	Closed,
	Unknown		UMETA(Hidden)
};