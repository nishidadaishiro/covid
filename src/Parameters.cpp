#include "Parameters.h"

#include "ofMain.h"
#include "ofxImGui.h"

Parameters::Parameters() {
    paramsPath = ofToDataPath("params.json");
}

void Parameters::drawGui() {
    if (ImGui::TreeNode("Static")) {
        ImGui::SliderInt("Initial population", &initialPopulation, 1, 10000);
        ImGui::SliderFloat("Initial vaccination rate", &initialVaccinationRate, 0, 1);
        ImGui::SliderFloat("Initial infection rate", &initialInfectionRate, 0, 1);
        array<int, 2> worldSize = {worldWidth, worldHeight};
        ImGui::InputInt2("World size", &worldSize[0]);
        worldWidth = worldSize[0];
        worldHeight = worldSize[1];
        
        ImGui::TreePop();
    }
    
    if (ImGui::TreeNode("Dynamic")) {
        ImGui::SliderFloat("Max movement", &maxMovement, 0, 10);
        ImGui::SliderFloat("Direction change probability", &directionChangeProbability, 0, 1);
        ImGui::SliderFloat("Infection Radius", &infectionRadius, 0, 100);
        ImGui::SliderFloat("Vacciation Probability", &vaccinationProbability, 0, 0.1);
        ImGui::SliderFloat("Infection Probability (not vaccinated)", &infectionProbability, 0, 1);
        ImGui::SliderFloat("Infection Probability (vaccinated)", &infectionProbabilityVaccinated, 0, 1);
        ImGui::SliderFloat("Symptom Probability", &symptomProbability, 0, 0.1);
        ImGui::SliderFloat("Recover Probability", &recoverProbability, 0, 0.1);
        
        ImGui::TreePop();
    }

    resetWorld = ImGui::Button("Reset");
}

void Parameters::save() {
    std::ofstream os(paramsPath);
    cereal::JSONOutputArchive archive( os );
    archive(cereal::make_nvp("params", *this));
}

void Parameters::load() {
    std::ifstream is(paramsPath);
    cereal::JSONInputArchive archive( is );
    archive(cereal::make_nvp("params", *this));
}
