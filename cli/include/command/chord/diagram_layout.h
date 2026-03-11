#pragma once

#include <string>
#include <vector>
#include <cstddef>

/**
 * @brief Organise plusieurs blocs ASCII côte à côte.
 *
 * Chaque élément de `blocks` doit être une chaîne multi-lignes
 * représentant un diagramme ASCII.
 *
 * @param blocks     Liste des diagrammes (format texte multi-lignes).
 * @param max_width  Largeur maximale disponible (ex: largeur terminal).
 * @param spacing    Nombre d'espaces entre les diagrammes.
 *
 * @return Une chaîne formatée contenant les diagrammes disposés
 *         en colonnes sur plusieurs lignes.
 */
std::string layout_blocks(
    const std::vector<std::string>& blocks,
    std::size_t max_width,
    std::size_t spacing = 4);

/**
 * @brief Découpe un bloc multi-lignes en lignes individuelles.
 *
 * Utile si vous souhaitez pré-traiter manuellement des diagrammes.
 */
std::vector<std::string>
split_lines(const std::string& block);