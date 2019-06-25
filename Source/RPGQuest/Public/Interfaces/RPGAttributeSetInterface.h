// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGAttributeSetInterface.generated.h"

class URPGAttributeSet;
// This class does not need to be modified.
UINTERFACE(Blueprintable)
class URPGAttributeSetInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class RPGQUEST_API IRPGAttributeSetInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IRPGAttributeSet")
	URPGAttributeSet* GetAttributeSetComp();
};
