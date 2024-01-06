// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "AliceBaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTALICE_API AAliceBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAliceBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	void InitInputActions();

	UPROPERTY()
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY()
	TObjectPtr<UInputAction> JumpAction;

	void OnMoveAction(const FInputActionInstance& Instance);
	void OnJumpAction(const FInputActionInstance& Instance);

//private:
//	// * ���
//	float Speed = 600.f;
//	float WalkSpeed = 300.f;
//	float ZoomInterpSpeed = 13.f;
//	// ��������
//	// �𸮾� ī�޶� FOV �⺻���� 90
//	// ������ FOV�� ����, ���ϴ� �� Theta, �⺻�� Default = 90, ���� rate
//	// FOVTheta = 2 * arctan(tan(FOVDefault / 2)/rate)
//	float ScopeRate = 2.f;
//	// * �����Ÿ�
//	float ZeroPoint = 100.f;
//
//	EPlayerState PlayerState = EPlayerState::Idle;
//	EWeaponType WeaponType = EWeaponType::SniperRifle;
//
//	FVector MeshLocation = FVector(50.f, 30.f, -20.f);
//	//FVector SRSightLocation = FVector(10.f, 0.f, -20.f);
//	FVector SRSightLocation = FVector(25.f, 0.f, -18.f);
//	FVector ARSightLocation = FVector(32.f, 0.f, -16.f);
//
//	// * �ɷ�ġ(��� �ɷ�ġ�� �Ѱ�� 100, �ּ� 0)
//	//float MaxHp = 100.f;
//	//float CurrentHp = 100.f; // ü��
//	//float Mentality = 100.f; // ���ŷ�
//	//float Satiety = 100.f; // ������
//	//float Stamina = 100.f; // ���¹̳�
//
//	//float SatietyHealthTime = 0.f; // ������ ������ �� ���� �ֱ⸶�� ü�°���
//
//	float BaseTurnRate;
//	float BaseLookUpRate;
//
//	// * �÷���
//	bool UseWeapon = false;
//	bool StartZoom = false;
//	bool IsZooming = false;
//	bool ReturnToZoom = false;
//	bool Slow = false;
//	bool IsRun = false;
//	bool IsNightVision = false;
//
//	UPROPERTY()
//	class UAnimMontage* Montage;
//
//	// * ������Ʈ
//	UPROPERTY()
//	class UCameraComponent* Camera;
//	UPROPERTY()
//	class USkeletalMeshComponent* MyMesh;
//	UPROPERTY()
//	class USphereComponent* InteractionSphere;
//
//	// * ����
//	UPROPERTY()
//	class AWeaponActor* Weapon;
//
//	// �̸� ������ ���� ��
//	UPROPERTY()
//	class AWeaponActor* WeaponSR;
//	UPROPERTY()
//	class AWeaponActor* WeaponAR;
//
//	// * SR ��Ʈ�׼�
//	void BoltActionFunction(float DeltaTime);
//
//	// * ���� �ݵ�
//	bool bRecoil = false;
//	bool bRecoilRecovery = false;
//
//	float RecoilTime = 0.f;
//	float RecoveryTime = 0.f;
//
//	FRotator RecoilStartRot;
//	FRotator RecoilDeltaRot = FRotator(2.f, 0.f, 0.f);
//
//	void RecoilStart();
//	void RecoveryStart();
//	void RecoilReset();
//
//	void RecoilFunction(float DeltaTime);
//
//	// * ������ ����
//	bool HoldingBreath = false; // ������
//	float BreathingAmplitude = 1.f;
//	float BreathingTime = 0.f;
//
//	void BreathFunction(float DeltaTime);
//
//	// * �Է� �Լ�
//	UFUNCTION()
//	void Inventory();
//	UFUNCTION()
//	void Pause();
//	UFUNCTION()
//	void Interact();
//
//	UFUNCTION()
//	void MoveForward(float AxisValue);
//	UFUNCTION()
//	void MoveRight(float AxisValue);
//	UFUNCTION()
//	void TurnAtRate(float AxisValue);
//	UFUNCTION()
//	void LookUpRate(float AxisValue);
//
//	UFUNCTION()
//	void Use();
//	UFUNCTION()
//	void BoltAction();
//
//	bool bBoltAction = false;
//	bool FireEnd = false;
//
//	UFUNCTION()
//	void ZoomOn();
//	UFUNCTION()
//	void Zoom(float AxisValue);
//
//	UFUNCTION()
//	void MeleeAttack();
//	UFUNCTION()
//	void Reload();
//
//	UFUNCTION()
//	void ZeroPointUp();
//	UFUNCTION()
//	void ZeroPointDown();
//
//	UFUNCTION()
//	void Run();
//
//	UFUNCTION()
//	void ChangeToSR();
//	UFUNCTION()
//	void ChangeToAR();
//
//	UFUNCTION()
//	void NightVisionOn();
//
//	// * ������ ���� �Լ�
//	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
//		AController* EventInstigator, AActor* DamageCauser) override;
//
//	// * ��Ÿ�� ��� ��ü�Լ�
//	float MyPlayMontage(FName SectionName, float speed = 1.f);
//
//	// * �ΰ����� ����
//	UPROPERTY()
//	class UAIPerceptionStimuliSourceComponent* Stimulus;
//
//	// * ������ ����
//	/*UPROPERTY()
//		TSubclassOf<UUserWidget> InventoryWidgetClass;
//	UPROPERTY()
//		class UInventoryWidget* InventoryWidget;*/
//
//	UPROPERTY()
//	TArray<class AItemActor*> DetectedItems;
//	/*UPROPERTY()
//		TArray<struct FItemSlot> ItemSlots;*/
//
//		//float InventoryWeight = 0.f;
//
//		// * �÷���
//	bool IsInventory = false;
//
//	// * InGame ����
//	UPROPERTY()
//	class UInGameWidget* InGameWidget;
//
//	UPROPERTY()
//	AActor* ActorForInteract;
//	UFUNCTION()
//	void StartDetection(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
//		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
//		bool bFromSweep, const FHitResult& SweepResult);
//	UFUNCTION()
//	void EndDetection(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
//		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
//
//	// * ����ť
//	UPROPERTY()
//	class USoundCue* GrassSound;
//	UPROPERTY()
//	class USoundCue* GroundSound;
//	UPROPERTY()
//	class USoundCue* StoneSound;
//	UPROPERTY()
//	class USoundCue* WaterSound;
//
//	// * �߰����ð�
//	UPROPERTY()
//	class USpotLightComponent* NightVisionLight;
//
//	// * ����
//	UPROPERTY()
//	class AWheeledVehicle* Vehicle;
//
//	// * ��(���̾ư��� �ý���
//	/*UPROPERTY()
//		class UNiagaraComponent* RainComponent;
//	UPROPERTY()
//		class UNiagaraSystem* RainSystem;*/
//
//public:
//	// * Getter
//	bool GetIsZooming() const { return IsZooming; }
//	float GetSpeed() const { return Speed; }
//	float GetZeroPoint() const { return ZeroPoint; }
//	//float GetScopeRate() const { return ScopeRate; }
//
//	/*float GetMaxHp() const { return MaxHp; }
//	float GetCurrentHp() const { return CurrentHp; }
//	float GetMentality() const { return Mentality; }
//	float GetSatiety() const { return Satiety; }
//	float GetStamina() const { return Stamina; }*/
//
//	class AWeaponActor* GetWeapon() const { return Weapon; }
//	EPlayerState GetMyPlayerState() const { return PlayerState; }
//	EWeaponType GetWeaponType() const { return WeaponType; }
//
//	//class UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
//	//float GetInventoryWeight() const { return InventoryWeight; }
//
//	void SetInGameWidget(UInGameWidget* widget) { InGameWidget = widget; }
//	void SetFireEnd(bool end) { FireEnd = end; }
//
//	TArray<AItemActor*> GetDetectedItems() const { return DetectedItems; }
//	//TArray<struct FItemSlot> GetItemSlots() const { return ItemSlots; }
//
//	// * ���� ���� �Լ�
//	void AttachToSocket(AActor* Actor, FName SocketName);
//	// * �÷��̾� ���� ���� �Լ�
//	void SetMyPlayerState(EPlayerState state);
//
//	// * ������ �Լ�
//	void AddDetectedItem(AItemActor* Item);
//	void RemoveDetectedItem(AItemActor* Item);
//
//	void RefreshUI();
//	void HideWeapon();
//	void ReadyWeapon();
//
//	void FootStep();
//	void SlowCharacter();
//
//	void SetVehicle(class AWheeledVehicle* vehicle) { Vehicle = vehicle; }
//	AWheeledVehicle* GetVehicle() const { return Vehicle; }
//
//	//void UseItem(FItemData itemData);
};
